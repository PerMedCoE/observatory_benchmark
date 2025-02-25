import xml.etree.ElementTree as ET
import json
import os

def update_param(root, param_name, param_value):
    """
    Updates an XML parameter by searching for the correct path, including named attributes.
    """
    xpath = param_name.replace(".", "/")  # Convert JSON-style keys to XML path

    # Special handling for microenvironment_setup.variable.oxygen.*
    if param_name.startswith("microenvironment_setup.variable.oxygen."):
        sub_param = param_name.split(".")[-1]  # Extract last key (e.g., Dirichlet_boundary_condition)

        # Find <variable name="oxygen">
        for var in root.findall(".//variable[@name='oxygen']"):
            # Handle Dirichlet_boundary_condition directly
            print(f"sub_param {sub_param}")
            if sub_param == "Dirichlet_boundary_condition":
                element = var.find(f"./{sub_param}")
                if element is not None:
                    element.text = str(param_value)
                    print(f"Updated: {param_name} -> {param_value}")
                    return

            # Handle Dirichlet_options.boundary_value cases
            if sub_param == "boundary_value":
                for bval in var.findall(".//Dirichlet_options/boundary_value"):
                    if "ID" in bval.attrib:
                        print("bval",bval)
                        bval.text = str(param_value)
                print(f"Updated: {param_name} -> {param_value}")
                return

    # Default case: try direct XPath search
    elements = root.findall(f".//{xpath}")
    if elements:
        for el in elements:
            el.text = str(param_value)
        print(f"Updated: {param_name} -> {param_value}")
        return

    print(f"Warning: Parameter '{param_name}' not found in XML")

def params_to_xml(json_data, default_xml, output_xml):
    """
    Reads an XML template, updates it using JSON parameters, and writes the modified XML to a new file.
    """
    if not os.path.exists(default_xml):
        print(f"Error: Default XML file '{default_xml}' not found.")
        return

    tree = ET.parse(default_xml)
    root = tree.getroot()

    for param, value in json_data.items():
        update_param(root, param, value)

    tree.write(output_xml)
    print(f"Saved updated XML as '{output_xml}'")

