Perfetto Federico! Ecco un esercizio **in stile esatto del prof** (come quelli che usi in lab), usando **thread/processi/segnali**, completo di vincoli, dettagli e obiettivi, pronto per essere implementato.

---

## 🧪 Esercizio: **`pingpong_signals.c` – Gestione cooperativa di segnali con fork e sincronizzazione**

### 🎯 **Obiettivo**
Creare un programma che lancia **due processi figli** tramite `fork()` (ping e pong). Questi due processi si scambiano segnali `SIGUSR1` a vicenda in maniera alternata per un numero `N` di volte, partendo da `ping`.

Il **padre**:
- gestisce la creazione dei processi,
- imposta un **signal handler** per `SIGINT` per terminare tutto in sicurezza,
- attende la fine dei due figli e riporta chi ha ricevuto più segnali.

---

### 📜 Requisiti

1. I due processi figli (`ping`, `pong`) devono:
   - **ignorare** `SIGINT` (`signal(SIGINT, SIG_IGN);`)
   - installare un **handler** per `SIGUSR1` che:
     - stampa `"ping [PID] ricevuto SIGUSR1"` o `"pong [PID] ricevuto SIGUSR1"`
     - incrementa un contatore interno
     - invia un `SIGUSR1` al **processo partner** (ping → pong, pong → ping)
     - termina se il numero di scambi raggiunge `N`

2. I due processi comunicano **solo tramite segnali**, senza pipe o memoria condivisa.

3. Il **padre**:
   - blocca `SIGUSR1` per evitare gestioni accidentali
   - gestisce `SIGINT`:
     - stampa `"Terminazione forzata"` e termina entrambi i figli con `SIGKILL`
   - usa `waitpid()` per raccogliere il valore di ritorno dei figli (numero di segnali ricevuti, passato con `exit(...)`)
   - stampa:
     ```c
     Ping ha ricevuto: X segnali
     Pong ha ricevuto: Y segnali
     ```

---

### 🧩 Interfaccia

```bash
./pingpong_signals.out N
```

- `N` è il numero **totale** di `SIGUSR1` da scambiare (es. 10: ping → pong → ping ... per 10 scambi totali).

---

### ✅ Esempio di output

```bash
ping [12345] ricevuto SIGUSR1
pong [12346] ricevuto SIGUSR1
ping [12345] ricevuto SIGUSR1
pong [12346] ricevuto SIGUSR1
...
Ping ha ricevuto: 5 segnali
Pong ha ricevuto: 5 segnali
```

---

### 💡 Suggerimenti implementativi

- Usa `pause()` per attendere i segnali in `ping` e `pong`.
- Usa `kill(pid, SIGUSR1)` per inviare segnali tra processi.
- Il PID del processo partner può essere passato tramite `argv[]` o `pipe()` iniziale (bloccante, poi chiusa).
- Usa `volatile sig_atomic_t` per contatori e flag di uscita.

---

### 🎁 Estensione opzionale
> Gestire anche `SIGTERM` con `sigaction()` nei figli per stampare un messaggio di chiusura personalizzato.

---

Se vuoi ti preparo anche lo scheletro iniziale di `main()` o una versione con `pthread` invece di `fork`. Vuoi procedere?