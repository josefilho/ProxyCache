<h1><center> Proxy Cache </center></h1>

<center>
<img src="https://img.shields.io/badge/Code%20by-NullByte-%237159c1?style=for-the-badge"/>
</center>

## Introdução

O cache proxy é um servidor intermediário entre o cliente e o servidor web. Quando um cliente solicita uma página web, o cache proxy verifica se a página já está armazenada em seu cache. Se a página estiver armazenada, o cache proxy a envia ao cliente. Se a página não estiver armazenada, o cache proxy solicita a página ao servidor web e armazena uma cópia em seu cache antes de enviá-la ao cliente.

## Sumário

- [Introdução](#introdução)
- [Sumário](#sumário)
- [Servidor](#servidor)
  - [Funcionamento](#funcionamento)
  - [Cache](#cache)
  - [Log](#log)
- [Cliente](#cliente)
  - [Funcionamento](#funcionamento-1)
  - [Cache](#cache-1)
  - [Log](#log-1)


## Objetivos

- Entender o funcionamento do cache proxy.
- Construir um servidor cache proxy.
- Construir um cliente para acesso ao servidor.

## Servidor

Para o servidor foi utilizado sockets para a comunicação com o cliente e o servidor web. O servidor foi implementado em C++ e utiliza a bibliotecas `winsock2.h` e `ws2tcpip.h` (Windows) e `sys/socket.h`, `netinet/in.h` e `arpa/inet.h` (Linux).

### Funcionamento

O servidor é iniciado com o comando `./proxy_server <porta> <tamanho_cache> <log> <algoritmo>` onde:
* `<porta>` é a porta em que o servidor irá escutar por conexões.
* `<tamanho_cache>` é o tamanho máximo do cache em MB.
* `<log>` é o nome do arquivo de log.
* `<algoritmo>` é o algoritmo de substituição de páginas a ser utilizado. Dentre esses: `LRU`, `LFU` e `FIFO`.

O servidor fica em um loop infinito, aguardando por conexões. Quando uma conexão é estabelecida, o servidor cria uma thread para atender a requisição. A thread fica em um loop infinito, aguardando por requisições. Quando uma requisição é recebida, o servidor verifica se a página está no cache. Se estiver, a página é enviada ao cliente. Se não estiver, o servidor solicita a página ao servidor web e armazena uma cópia em seu cache antes de enviá-la ao cliente.

### Cache

O cache é implementado com um map que tem como indice o nome da página e como valor um objeto `Page`. O objeto `Page` contém o conteúdo da página, o tamanho da página, a data de criação e a quantidade de vezes que a página foi acessada. O tamanho do cache é limitado pelo parâmetro `<tamanho_cache>` passado ao servidor. Quando o cache está cheio, o servidor utiliza o algoritmo de substituição de páginas passado pelo parâmetro `<algoritmo>` para remover uma página do cache.

### Log

O log é implementado com um arquivo de texto. Quando uma requisição é recebida, o servidor escreve no log o endereço IP do cliente, a data e hora da requisição, o nome da página requisitada e o tamanho da página.
O log também é utilizado para armazenar as estatísticas do servidor. Quando o servidor é finalizado, ele escreve no log as estatísticas de uso do cache.	

## Cliente

Para o cliente foi utilizado sockets para a comunicação com o servidor. O cliente foi implementado em C++ e utiliza a bibliotecas `winsock2.h` e `ws2tcpip.h` (Windows) e `sys/socket.h`, `netinet/in.h` e `arpa/inet.h` (Linux).

### Funcionamento

O cliente é iniciado com o comando `./proxy_client <ip_servidor> <porta_servidor>` onde:
* `<ip_servidor>` é o endereço IP do servidor.
* `<porta_servidor>` é a porta em que o servidor está escutando por conexões.

O cliente fica em um loop infinito, aguardando por comandos. Quando um comando é recebido, o cliente envia o comando ao servidor. O servidor responde com o conteúdo da página requisitada ou com uma mensagem de erro.

### Comandos

Os comandos aceitos pelo cliente são:
* `GET <nome_pagina>`: requisita a página `<nome_pagina>` ao servidor.
* `STATS`: requisita as estatísticas de uso do cache ao servidor.
* `EXIT`: finaliza a conexão com o servidor.


# Referências


* Computer Networking: *A Top-Down Approach (6th Edition)* - **Kurose, James F. and Ross, Keith W**.

* [Sockets Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)


