a = arduino('COM3', 'Uno', 'Libraries', {'Servo', 'Ultrasonic'});

% Create servo objects
s_low = servo(a, 'D4');
s_up = servo(a, 'D3');
sensor = addon(a, 'Ultrasonic', 'D6', 'D5');

% Initialize arrays
num_points = 130*4*2; % 130 steps per direction, 4 times (two loops), and 2 for each step
radius = zeros(1, num_points);
phi_arr = zeros(1, num_points);
theta_arr = zeros(1, num_points);
i = 1;

theta = 0.5194444444444;

while theta <= 160/180            % Loop until theta reaches 160 degrees
    theta = theta + 1/180;
    for phi = 1/180 : 1/180 : 130/180
        writePosition(s_low, phi);
        writePosition(s_up, theta);
        dist = readDistance(sensor);
        
        radius(i) = dist * 100; % Convert distance to centimeters
        phi_arr(i) = phi;
        theta_arr(i) = theta;
        i = i + 1; % Increment index
    end

    theta = theta + 1/180;
    for phi = 130/180 : -1/180 : 0/180
        writePosition(s_low, phi);
        writePosition(s_up, theta);
        dist = readDistance(sensor);
        
        radius(i) = dist * 100; % Convert distance to centimeters
        phi_arr(i) = phi;
        theta_arr(i) = theta;
        i = i + 1; % Increment index
    end
end
