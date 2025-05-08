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
    cities = {}
    with open(filePath, 'r') as file:
        for _ in range(int(skip_lines)):
            next(file)

        for line in file:
            if "EOF" in line or line.strip() == "":
                break
            parts = line.strip().split()
            if len(parts) < 3:
                continue
            city_id = int(parts[0])
            x = float(parts[1])
            y = float(parts[2])
            cities[city_id] = (x, y)
    return cities


if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("Invalid amount of arguments")
        exit(1)

    cities_file_name = sys.argv[1]
    cities_skip_lines = sys.argv[2]

    order = load_order()    
    cities = load_cities(cities_file_name, cities_skip_lines)    


    coords = [cities[i] for i in order]
    x, y = zip(*coords)

    plt.scatter(*zip(*cities.values()), c='blue', s=100, label='Cities')
    plt.plot(x, y, 'r-', linewidth=2, label='Path')

    for city_id, (x_i, y_i) in cities.items():
        plt.text(x_i + 0.2, y_i + 0.2, str(city_id), fontsize=9)

    plt.title("Travelling Salesman Route")
    plt.legend()
    plt.grid(True)
    plt.axis("equal")
    plt.show()