import serial
import csv

# Open serial connection to Arduino
ser = serial.Serial('COM3', 115200)  # Change 'COM3' to your serial port

# Open CSV file for writing
with open('data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)

    # Read and save data from Arduino indefinitely
    while True:
        # Read line from serial port
        line = ser.readline().strip()
        print(line)  # Print received line (optional)

        # Split line into values and write to CSV file
        data = line.split(',')
        csvwriter.writerow(data)
