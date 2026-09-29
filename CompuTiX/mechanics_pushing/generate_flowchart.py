import argparse
import sys
import yaml

from pathlib import Path

def action_count( comp ):
    result = 0
    for c in comp["children"]:
        if is_action( c ):
            result += 1

    return result

def is_action( comp ):
    if comp["component_type"] == "ComponentStorage":
        return False
    if comp["component_type"] == "DegreeOfFreedom":
        return False
    if comp["component_type"] == "Parameter":
        return False
    if comp["component_type"] == "Collection":
        return False

    return True

def print_component( comp, 
                     depth = 0,
                     max_depth = 64,
                     condition_counter = 0, 
                     follows_condition = False, 
                     stack = [ "stop" ] ) -> ( str, bool, int ):
    match comp["component_type"]:
        case "ComponentStorage" | "DegreeOfFreedom" | "Parameter" | "Collection":
            return "", follows_condition, condition_counter 

    if "::Triggers::" in comp["component_type"]:
        if follows_condition:
            return f'''elseif ({comp["name"]}\\n{comp["component_type"]}) then (false)
{stack[-1]}
''', True, condition_counter 
        else:
            return f'''if ({comp["name"]}\\n{comp["component_type"]}) then (false)
{stack[-1]}
''', True, condition_counter + 1 


    result = ''
    if follows_condition:
        result += 'else (true)\n' 
        follows_condition = False

    if comp["component_type"] == "OnActions::Loop" and depth < max_depth:
        stack.append( "break" )
        initial_counter = condition_counter
        result += f'''partition "{comp["name"]}\\n{comp["component_type"]}" {{
while (true) 
'''
        for c in comp["children"]:
            if is_action( c ):
                r, follows_condition, condition_counter = print_component( c, depth + 1, max_depth, condition_counter, follows_condition, stack )
                result += r 
        while condition_counter > initial_counter:
            result += f'endif\n'
            condition_counter -= 1 
        result += f'endwhile (false)\n}}\n'
        stack.pop()
        return result, False, condition_counter  

    if action_count( comp ) > 0 and depth < max_depth:
        stack.append( "" )
        initial_counter = condition_counter
        result += f'partition "{comp["name"]}\\n{comp["component_type"]}" {{\n'
        for c in comp["children"]:
            if is_action( c ):
                r, follows_condition, condition_counter = print_component( c, depth + 1, max_depth, condition_counter, follows_condition, stack )
                result += r 
        while condition_counter > initial_counter:
            result += f'endif\n'
            condition_counter -= 1 
        result += f'(E)\n}}\n' 
        stack.pop()
        return result, False, condition_counter 
    
    result += f':{comp["name"]}\\n{comp["component_type"]};\n'
    return result, False, condition_counter

def generate_flowchart( root: dict, max_depth: int ) -> str:
    result = '''@startuml
!pragma useVerticalIf on
skinparam DefaultTextAlignment center
skinparam ConditionEndStyle hline
start
'''
    uml, *_ = print_component( root, max_depth = max_depth )
    result += uml
    result += '''stop
@enduml
'''
    
    return result

def main( args: list = sys.argv[1:] ) -> None:
    """
    Parses arguments and generate UML scheme of simulation.

    Use '-h' or '--help' for available options.

    Parameters:
     args - command line arguments. By default: sys.argv
    """
    # Prepare argument parser 
    parser = argparse.ArgumentParser( description = "Generates flow chart as an UML file" )
    parser.add_argument( 'FILE', 
                         nargs="?",
                         default="log.yaml",
                         type=Path,
                         help="Log file which will be used for generating the simulation flow chart. Default: log.yaml" )
    parser.add_argument( '-r',
                         '--root',
                         default="Final tree",
                         help="Determines key, under which there is the root component of the simulation. Default: Final tree" )
    parser.add_argument( '-i',
                         '--index',
                         default=0,
                         type=int,
                         help="Zero based index of the simulation to be visualized. Default: 0" )
    parser.add_argument( '-o',
                         '--output',
                         type=Path,
                         help="Output UML file. By default the same as 'file' with extension replaced with '.uml'." )
    parser.add_argument( '-d',
                         '--depth',
                         type=int,
                         default=64,
                         help="Maximal depth for the print out. Default: 64" )
    params = parser.parse_args( args )

    # Parse log file
    with open(params.FILE,"r") as f:
        log = yaml.safe_load(f)
        root = log[params.index][params.root][0]

    # Generate the UML
    uml = generate_flowchart( root, params.depth )

    # Store output 
    if params.output is not None:
        output = params.output
    else:
        output = params.FILE.with_suffix( '.uml' )
    with open( output, "w" ) as f:
        f.write( uml )

# Run main if nothing provided
if __name__ == "__main__":
    main()

