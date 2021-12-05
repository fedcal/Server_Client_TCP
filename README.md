# Server_Client_TCP

Esercizio sul protocollo TCP. Testo:

Il client legge da riga di comando l'indirizzo e il numero di porta del server (es. 60000), dopodiché richiede la connessione al server.
Ricevuta la connessione, il server visualizza sullo standard output l'indirizzo e il numero di porta del client, scrivendo "Connection established with xxx.xxx.xxx.xxx:yyyyy".
Stabilita la connessione, il client legge l'operazione da compiere (usando i caratteri +, x, -, /, rispettivamente per Addizione, Moltiplicazione, Sottrazione e Divisione) e due numeri interi dallo standard input (es. + 23 45) ed invia al server quanto letto da tastiera.
  
  1. Il server legge quanto inviato dal client, esegue l'operazione richiesta e invia il risultato al client (es. 68).
  2. Il client legge la risposta inviata dal server e la visualizza sullo standard output.
  3. Il client legge dallo standard input la successiva operazione da compiere.
  4. Se invece di un'operazione è inserito il carattere =, il client chiude la connessione con il server e termina qui il suo processo; altrimenti, torna al punto 3.
  5. Il server non termina mai il suo processo e deve essere in grado di accettare una coda massima di 5 client (parametro qlen).

REQUISITI

  1. Il protocollo applicativo condiviso fra client e server deve essere specificato tramite file header .h.
  2. Creare le funzioni matematiche utilizzando i seguenti nomi: add(), mult(), sub() e division().
  3. La lettura da riga di comando è effettuata in una singola lettura (ossia + 23 45[invio], non +[invio]23[invio]45[invio]).
  4. Il client e il server devono potersi avviare senza parametri passati da riga di comando, ossia useranno un indirizzo ip e numero di porta predefiniti.
  5. Le operazioni sono da intendersi indipendenti l'una dall'altra (ossia, i risultati delle operazioni non sono cumulativi).


[www.federicocalo.it](www.federicocalo.it)
