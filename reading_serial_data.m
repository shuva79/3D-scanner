% The code does work but everytime you stop it, you'll have you restart it
% because the port is shown to be occupied by the previous iteration of the
% code.

% This shit finally worked, god bless

% Define the serial port settings
port = 'COM3'; % Change this to the correct port
baudrate = 115200; % Change this to match the baudrate of your device

%creating an array to store the three axes
x_array = [];
y_array = [];
z_array = [];
i=0;

% create a figure for the axes (realtime shit hehe)
figure;
plot3(x_array, y_array, z_array, 'b.'); %plot values
%labels for the figure
xlabel('X');
ylabel('Y');
zlabel('Z');
title('Pelotas');
grid on;
hold on;

%creating file for csv
file = fopen('csv/data.txt','w');

% Open the serial port
s = serialport(port, baudrate);
s.Timeout = 20;  % Set timeout to 20 seconds
% Read and display live data
while true
    try
        % Read data from the serial port
        data = readline(s);
        
        % Display the received data
        %fprintf("%s\n",data);
        csvArray = csvToDouble(data);
        if ~isnan(csvArray(1)) && csvArray(1) < 1000
            disp(["First value: ", csvArray(1)]);
            radius = csvArray(1);
            phi = csvArray(2);
            theta = csvArray(3);
            [x_array(end+1), y_array(end+1), z_array(end+1)] = valueToCartesian(radius, phi, theta);
            
            % We update the plot now
            plot3(x_array(end), y_array(end), z_array(end), 'r.');
            drawnow;    % Force to plot immediately

            fprintf(file, "%.3f,%.3f,%.3f\n", x_array(end), y_array(end), z_array(end));
        end
     catch ME
        fclose(file);       % close the file during keyboard interrupt
        clear s;
    end
end

% Close the serial port when done
clear s;

% Close the file normally (prolly wont happen tho lmaoo)
fclose(file);

function float_value = csvToDouble(value)
    data_value = strsplit(value, ',');
    float_value = str2double(data_value);
    
end

function [x_axis, y_axis, z_axis] = valueToCartesian(radius, phi, theta)
    x_axis = ( radius*sin(theta)*cos(phi) );
    y_axis = ( radius*sin(theta)*sin(phi) );
    z_axis = ( radius*cos(theta) ) ;
end
