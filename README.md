Challenge FIAP 2026 - Sistema de Validação de Telemedicina Veterinária com RFID e Node-RED
Descrição do Projeto
Este projeto consiste em um sistema de segurança, auditoria e conformidade para a emissão de receitas médicas em plataformas de telemedicina veterinária. O objetivo principal é garantir a validação física da presença e da situação cadastral do médico veterinário antes da assinatura digital de qualquer documento clínico.

O sistema integra hardware de leitura por radiofrequência (RFID) a um ecossistema local de orquestração de dados e interface web, simulando de ponta a ponta as camadas de hardware, comunicação, regras de negócio e barramento de dados corporativo.

Arquitetura de Comunicação e Fluxo de Dados
O projeto opera de forma híbrida utilizando dois modelos de comunicação distintos:

Camada de Hardware para Back-end (Serial Puro/UART): O microcontrolador Arduino comunica-se diretamente com o servidor Node-RED via cabo USB (Porta COM). O tráfego de dados é feito em texto bruto (Stream de caracteres) na velocidade padrão de 9600 Baud. Não há uso de pacotes de rede ou endereçamento IP nesta etapa.

Camada de Back-end para Front-end (HTTP / WebSockets): O Node-RED atua como um servidor local web. A renderização da Dashboard e a atualização dos dados em tempo real no navegador do usuário final utilizam requisições HTTP e canais WebSockets estáveis.

Sequência do Fluxo
O profissional aproxima a tag RFID do leitor MFRC522.

O Arduino faz a varredura física, identifica o UID da tag e o transmite via conexão serial.

O Node-RED recebe o dado, aplica um filtro de temporização (Rate Limit) para ignorar leituras duplicadas e valida o ID recebido.

Caso o ID corresponda a um profissional ativo, os dados da receita correspondente são carregados na Dashboard Web e o hardware ativa o LED Verde e um sinal sonoro de sucesso no Buzzer.

Caso o ID corresponda a um profissional com restrição ou registro inativo, o sistema bloqueia a emissão na interface e aciona o LED Vermelho e sinais sonoros de alerta em loop.

Componentes do Projeto
Hardware
Microcontrolador: Arduino Uno R3

Módulo de Leitura: RFID MFRC522 (Frequência de operação: 13.56 MHz)

Atuadores: 1x Buzzer Ativo, 1x LED Verde, 1x LED Vermelho

Componentes de Proteção: Resistores de 220Ω acoplados nas linhas dos LEDs e do Buzzer (essencial para limitar o consumo de corrente e prevenir quedas de tensão na porta USB do computador).

Softwares e Bibliotecas
Firmware: Linguagem C++ desenvolvida na Arduino IDE, utilizando as bibliotecas nativas SPI.h e MFRC522.h.

Gerenciador de Escopo: Node-RED executado sobre o ambiente Node.js.

Módulos do Node-RED: node-red-node-serialport para controle de fluxo serial e node-red-dashboard para construção da interface gráfica.
