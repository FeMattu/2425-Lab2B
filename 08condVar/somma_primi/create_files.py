import random
import os
import sys

def crea_file_casuali(n, k, directory="output"):
    os.makedirs(directory, exist_ok=True)

    for i in range(n):
        nome_file = os.path.join(directory, f"file_{i+1}.txt")
        with open(nome_file, "w") as f:
            for _ in range(k):
                numero = random.randint(0, 100)
                f.write(f"{numero}\n")

    print(f"{n} file creati nella cartella '{directory}' con {k} numeri ciascuno.")

def main(n,k):
    try:
        assert n > 0 and k > 0
        crea_file_casuali(n, k)
    except ValueError:
        print("Errore: inserisci numeri interi validi.")
    except AssertionError:
        print("Errore: n e k devono essere > 0.")


if __name__ == "__main__":
    if len(sys.argv) == 3:
        main(int(sys.argv[1]), int(sys.argv[2]))
    else:
        print("Uso:", sys.argv[0], "numero_files ", "numeri_per_file")
    

