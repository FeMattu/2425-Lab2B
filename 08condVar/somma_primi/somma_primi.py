import os
import sys
import subprocess

def run_sommaprimi(directory=""):
    if not os.path.isdir(directory):
        print("Errore: directory non valida.")
        return

    # Prende tutti i file (con path completo)
    listafile = sorted(
        os.path.join(directory, f) for f in os.listdir(directory)
        if os.path.isfile(os.path.join(directory, f))
    )

    if not listafile:
        print("Nessun file trovato nella directory.")
        return
    
    cmd = os.path.join("./somma_primi/somma_primi_files.out ") + " ".join(listafile)

    print(cmd)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        run_sommaprimi(sys.argv[1])
    else:
        print("Uso:", sys.argv[0], "directory_files_di_input")
