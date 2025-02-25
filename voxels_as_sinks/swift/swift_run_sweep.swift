import io;
import sys;
import files;
import string;
import python;
import R;

string emews_root = getenv("EMEWS_PROJECT_ROOT");
string turbine_output = getenv("TURBINE_OUTPUT");

string to_xml_code =
"""
import params2xml
import json
params = json.loads('%s')
params['user_parameters.random_seed'] = '%s'

default_settings = '%s'
xml_out = '%s'

params2xml.params_to_xml(params, default_settings, xml_out)
""";



app (file out, file err) run_model (file shfile, string executable, string param_line, string instance)
{
    "bash" shfile executable param_line emews_root instance @stdout=out @stderr=err;
    //trace("run model");
}

app (void o) get_mean (file summarize_py, string instance_dir) {
    "python" summarize_py instance_dir;
}

app (void o) plot_all (file plot_py, string turbine_output) {
    "python" plot_py turbine_output;
}

app (void o) make_dir(string dirname) {
  "mkdir" "-p" dirname;
}

app (void o) make_output_dir(string instance) {
  "mkdir" "-p" (instance+"/output");
}

// deletes the specified directory
app (void o) rm_dir(string dirname) {
  "rm" "-rf" dirname;
}

main() {

  string executable = argv("exe");
  string default_xml = argv("settings");

  file model_sh = input(emews_root + "/scripts/growth_model.sh");
  file upf = input(argv("parameters"));
  file summarize_py = input(emews_root + "/scripts/get_mean_csv.py");
  // file plot_py = input(emews_root + "/scripts/plot_all.py");
  trace("main");
  
  string results[];
  string upf_lines[] = file_lines(upf);

  foreach params,i in upf_lines {
    string instance_dir = "%s/instance_%i/" % (turbine_output, i+1);
    make_dir(instance_dir) => {
      make_output_dir(instance_dir) => {
        string xml_out = instance_dir + "/output/settings.xml";
        string code = to_xml_code % (params, i, default_xml, xml_out);
        file out <instance_dir+"out.txt">;
        file err <instance_dir+"err.txt">;
        trace(params);
        trace("Processing instance:", i);
        python_persist(code, "'ignore'") => {
          (out,err) = run_model(model_sh, executable, xml_out, instance_dir) => {
          get_mean (summarize_py, instance_dir);
            //  =>
            // plot_all(instance_dir + "output/");
          }
        }
      }
    }
  }
  // plot_all (plot_py, turbine_output);

  // string results_str = string_join(results, ",");
  // string code = find_min % results_str;
  // string mins = R(code, "toString(res)");
  // string min_idxs[] = split(mins, ",");
  // string best_params[];
  // foreach s, i in min_idxs {
    // int idx = toint(trim(s));
    // best_params[i] = upf_lines[idx - 1];
  // }
  //file best_out <turbine_output + "/output/best_parameters.txt"> =
  //  write(string_join(best_params, "\n"));
}
