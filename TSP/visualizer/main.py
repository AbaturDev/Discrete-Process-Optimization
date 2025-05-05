import matplotlib.pyplot as plt
import os
import sys

base_dir = os.path.dirname(__file__)
data_folder_dir = os.path.join(base_dir, "..", "data")

def load_order():
    filePath = os.path.join(data_folder_dir, "solution_order.txt")

    with open(filePath, 'r') as file:
        return [int(x) for x in file.read().strip().split()]

def load_cities(filename, skip_lines):
    filePath = os.path.join(data_folder_dir, filename)


if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("Invalid amount of arguments")
        exit(1)

    cities_file_name = sys.argv[1]
    cities_skip_lines = sys.argv[2]

    order = load_order()    
    cities = load_cities(cities_file_name, cities_skip_lines)    



# x = [cities[i][0] for i in order]
# y = [cities[i][1] for i in order]

# plt.scatter(*zip(*cities), c='blue', s=100, label='Miasta')

# plt.plot(x, y, 'r-', linewidth=2, label='Trasa')

# for i, (x_i, y_i) in enumerate(cities):
#     plt.text(x_i + 0.1, y_i + 0.1, str(i), fontsize=12)

# plt.title("Trasa Komiwojażera")
# plt.legend()
# plt.grid(True)
# plt.axis("equal")
# plt.show()
