import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Example plot points for three sets of data
x1 = [1, 2, 3, 4, 5]
y1 = [2, 3, 4, 3, 2]
z1 = [1, 2, 3, 4, 5]

x2 = [1, 2, 3, 4, 5]
y2 = [5, 4, 3, 2, 1]
z2 = [5, 4, 3, 2, 1]

x3 = [1, 2, 3, 4, 5]
y3 = [1, 2, 3, 4, 5]
z3 = [3, 2, 4, 5, 1]

# Create a new figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the data points as scatter plots
ax.scatter(x1, y1, z1, label='Line 1')
ax.scatter(x2, y2, z2, label='Line 2')
ax.scatter(x3, y3, z3, label='Line 3')

# Connect the data points with lines
ax.plot(x1, y1, z1, color='blue', alpha=0.6)
ax.plot(x2, y2, z2, color='orange', alpha=0.6)
ax.plot(x3, y3, z3, color='green', alpha=0.6)

# Add labels and legend
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')
ax.set_title('3D Scatter Plot with Connected Data Points')
ax.legend()

# Show the plot
plt.show()
