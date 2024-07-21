import csv

def convert_to_csv(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w', newline='') as outfile:
        reader = infile.readlines()
        writer = csv.writer(outfile)
        for line in reader:
            # Remove newline character and split values by comma
            values = line.strip().split(',')
            # Write values to CSV file
            writer.writerow(values)

# Example usage
input_file = 'data.txt'  # Replace with your input file name
output_file = 'data.csv'  # Replace with your desired output file name
convert_to_csv(input_file, output_file)
