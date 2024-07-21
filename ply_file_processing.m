clear
clc

ptCloudA = pcread('ply/output.ply');% read the point cloud .ply file

% point cloud diagram
figure(3)
pcshow(ptCloudA); % initial plot data
title('1: InitialPoint cloud');

noise = rand(500, 3);
ptCloudX = pointCloud([ptCloudA.Location; noise]);

figure
pcshow(ptCloudX);
title('Noisy Data');

% denoising
nearest_neighbour = 10;
theta = 0.05;
% Denoise algorithm using above parameters
ptCloudB = pcdenoise(ptCloudA, 'NumNeighbors',nearest_neighbour, 'Threshold',theta); 
figure(4);
pcshow(ptCloudB);
title("2: Denoising");

% Segmentation
minDistance = 2; % minimum distance to nearest neighbour (in cms)
[labels, numClusters] = pcsegdist(ptCloudB, minDistance); % generate labels to each point cloud
figure(5)
colours = pcshow(ptCloudB.Location, labels); % show segmentation results by colours
colormap(hsv(numClusters))
title("3: Segmentation");

% Adding surfaces
colour_rgb = [0,0,0];

for i=1:1:max(labels)   % looping through the different labels 
    pointcloud1 = select(ptCloudB, find(labels == i)); % for each label we select the points
    % extracting coordinates from point cloud
    x = pointcloud1.Location(:,1);
    y = pointcloud1.Location(:,2);
    z = pointcloud1.Location(:,3);

    x = double(x);
    y = double(y);
    z = double(z);

    % alpha shapes method
    shape = alphaShape(x,y,z,1)
    h = plot(shape)             % plotting the alpha shapes
    h.FaceColor = colour_rgb;% giving each label a different colour
    title("4: Surface fitting - Alpha Shape");
    
    hold on;
end

hold off