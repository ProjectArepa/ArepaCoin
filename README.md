# Arepacoin

![logo](https://chainz.cryptoid.info/logo/arepa.png)

Arepacoin nace el 25 de septiembre del 2016 con el fin de convertirse en una moneda referente de Venezuela en el mundo, con una emisión total de 60.000.000 de Arepas y un PoS del 3% de interés anual. Esta desarrollada con el algoritmo Scrypt PoW-PoS, que le permite ser una moneda robusta con un crecimiento de forma orgánica y con gran solidez. Puerto RPC: 8586 y Puerto P2P: 8585. 

Los bloques minables mediante PoW tienen una recompensa generada de la siguiente manera:
=========================
* Bloques 1 hasta 10000 tiene una recompensa de 325 Arepas.
* Bloques 10001 hasta 250000 tienen una recompensa de 50 Arepas.
* Bloques 250001 hasta 500000 tendran una recompensa de 25 Arepas.
* Bloques 500001 hasta 700000 tendran una recompensa de 12 Arepas.
* Bloques 700001 hasta 1000000 tendran una recompensa de 6 Arepas.
* Bloques 1000001 hasta 2000000 tendran una recompensa de 3 Arepas.
* Bloques 2000001 en adelante tendran una recompensa de 1 Arepa.

LINKS
==========================
* Pagina Oficial (https://arepacoinve.info/)
* Foro Oficial (https://bitcointalk.org/index.php?topic=2931570)
* Twitter Arepacoin (https://twitter.com/arepacoinve)
* Grupo Telegram Arepacoin (https://t.me/ArepacoinVE_ES)

Procedimiento para compilar la billeterá virtual en Ubuntu GNU/Linux:
==========================
Escribir en la terminal los siguientes comandos:

```bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install git
git clone https://github.com/ProjectArepa/Arepacoin
cd Arepacoin

## Para Ubuntu 16.04 y 18.04.
./Compile.sh
./Arepacoin-qt
```