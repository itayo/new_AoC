import sys
import os
import shutil

# Check if the correct number of arguments is passed
if len(sys.argv) != 2:
    print("Usage: python generate_day.py <day_number>")
    sys.exit(1)

# Get the day number from the command-line arguments
day_number = str(sys.argv[1]).zfill(2)

# Validate that the day number is in the format of two digits (e.g., 01, 02, 03)
if not day_number.isdigit() or len(day_number) != 2:
    print("Invalid day number. Please provide a valid two-digit day number (e.g., 01, 02).")
    sys.exit(1)

# Template file paths (assume these exist as DayXX.c and DayXX.h templates)
template_header_path = "../templates/DayXX.h"
template_cpp_path = "../templates/DayXX.cpp"

# Destination file paths
header_file = f"include/Day{day_number}.h"
cpp_file = f"src/Day{day_number}.cpp"
cmake_list = f"CMakeLists.txt"
main_cpp = f"main.cpp"

# Check if the files already exist
if os.path.exists(header_file) or os.path.exists(cpp_file):
    print(f"Day {day_number} already exists.")
    sys.exit(1)

# Copy and replace in the header template
if os.path.exists(template_header_path):
    shutil.copy(template_header_path, header_file)
    # Read and replace content in the header file
    with open(header_file, 'r') as file:
        content = file.read()
    content = content.replace("XX", f"{day_number}")
    with open(header_file, 'w') as file:
        file.write(content)
else:
    print(f"Template header file {template_header_path} not found.")
    sys.exit(1)

# Copy and replace in the cpp template
if os.path.exists(template_cpp_path):
    shutil.copy(template_cpp_path, cpp_file)
    # Read and replace content in the cpp file
    with open(cpp_file, 'r') as file:
        content = file.read()
    content = content.replace("XX", f"{day_number}")
    with open(cpp_file, 'w') as file:
        file.write(content)
else:
    print(f"Template cpp file {template_cpp_path} not found.")
    sys.exit(1)
    
if os.path.exists(cmake_list):
    print("trying to patch CMAKE")
    with open(cmake_list, 'r') as file:
        content = file.read()
    content = content.replace(" )#DayInsertPlace", f" src/Day{day_number}.cpp )#DayInsertPlace")
    with open(cmake_list, 'w') as file:
        file.write(content)
else:
    print(f"Cmake file {cmake_list} not found.")
        
if os.path.exists(main_cpp):
    print("trying to patch main.cpp")
    with open(main_cpp, 'r') as file:
        content = file.read()
    content = content.replace("//DayHeader", f"#include \"Day{day_number}.h\"\n//DayHeader")
    make_unique = "days.push_back({std::make_unique<Day" + day_number + ">(), \""+ day_number + "\"});"
    content = content.replace(f"//dayCreator",f"{make_unique}\n    //dayCreator")
    with open(main_cpp, 'w') as file:
        file.write(content)
else:
    print(f"main.cpp not found.")
       
with open(f"Data/input{day_number}A.txt", 'w') as fp:
    pass   
with open(f"Data/input{day_number}B.txt", 'w') as fp:
    pass       
with open(f"TestData/input{day_number}A.txt", 'w') as fp:
    pass       
with open(f"TestData/input{day_number}B.txt", 'w') as fp:
    pass       

print(f"Day {day_number} files created successfully.")
