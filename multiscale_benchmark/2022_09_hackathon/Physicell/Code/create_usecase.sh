# script that generated the folders and the apropriate makefiles for generating sample project for physicell
if [ $# -ne 2 ]; then
  echo "Error: Expected two arguments, but got $#"
  exit 1
else
  echo "The script was called with two arguments: $1 and $2"
fi

if "$2" == "physicell"
# call python?
elif "$2" == "intracellular"
elif "$2" == "physiboss"
fi 