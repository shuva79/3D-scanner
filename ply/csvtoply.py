

def csv_to_ply(csv_file, ply_file):
    # Read CSV file
    with open(csv_file, 'r') as f:
        lines = f.readlines()

    # Parse coordinates
    vertices = []
    for line in lines:
        x, y, z = map(float, line.strip().split(','))
        vertices.append((x, y, z))

    # Write PLY file
    with open(ply_file, 'w') as f:
        # Header
        f.write("ply\n")
        f.write("format ascii 1.0\n")
        f.write("element vertex {}\n".format(len(vertices)))
        f.write("property float x\n")
        f.write("property float y\n")
        f.write("property float z\n")
        f.write("end_header\n")

        # Vertices
        for vertex in vertices:
            f.write("{} {} {}\n".format(vertex[0], vertex[1], vertex[2]))


csv_file = "../csv/data.txt"
ply_file = "output.ply"
csv_to_ply(csv_file, ply_file)
