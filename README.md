MEMBROS DA EQUIPE CTech

João Victor Vendrameto - RM 563665 - 2TDSPV
Nicolas de Oliveira Jacob - RM 564205 - 2TDSPX
Gabriel Ambrósio Saraiva - RM 566552 - 2TDSPV
Vinicius Romaguera Cardozo - RM 562308 - 2TDSPX
Yuri Fuzinatto Garzoli Barreto - RM 561450 - 2TDSPX


----------------------------------------------------------------------------------------------------------------------------------------------------------------


Challenge FIAP 2026 - Sistema de Validação de Telemedicina Veterinária com RFID e Node-RED
Descrição do Projeto
Este projeto consiste em um sistema de segurança, auditoria e conformidade para a emissão de receitas médicas em plataformas de telemedicina veterinária. O objetivo principal é garantir a validação física da presença e da situação cadastral do médico veterinário antes da assinatura digital de qualquer documento clínico.





O sistema integra hardware de leitura por radiofrequência (RFID) a um ecossistema local de orquestração de dados e interface web, simulando de ponta a ponta as camadas de hardware, comunicação, regras de negócio e barramento de dados corporativo.

Arquitetura de Comunicação e Fluxo de Dados
O projeto opera de forma híbrida utilizando dois modelos de comunicação distintos:

Camada de Hardware para Back-end (Serial Puro/UART): O microcontrolador Arduino comunica-se diretamente com o servidor Node-RED via cabo USB (Porta COM). O tráfego de dados é feito em texto bruto (Stream de caracteres) na velocidade padrão de 9600 Baud. Não há uso de pacotes de rede ou endereçamento IP nesta etapa.

Camada de Back-end para Front-end (HTTP / WebSockets): O Node-RED atua como um servidor local web. A renderização da Dashboard e a atualização dos dados em tempo real no navegador do usuário final utilizam requisições HTTP e canais WebSockets estáveis.

Componentes do Projeto
Hardware e Eletrônica
Microcontrolador: Arduino Uno R3

Módulo de Leitura: RFID MFRC522 (Frequência de operação: 13.56 MHz)

Atuadores: Buzzer Ativo, LED Verde, LED Vermelho

Matriz de Contatos (Protoboard): Utilizada para a distribuição das linhas de alimentação (GND/VCC) e organização mecânica e elétrica dos resistores, LEDs e buzzer sem necessidade de soldagem.

Componentes de Proteção: Resistores de 220Ω acoplados nas linhas dos LEDs e do Buzzer (essencial para limitar o consumo de corrente, evitar a queima dos componentes e prevenir quedas de tensão na porta USB do computador).

Softwares e Bibliotecas
Firmware: Linguagem C++ desenvolvida na Arduino IDE, utilizando as bibliotecas nativas SPI.h e MFRC522.h.

Gerenciador de Escopo: Node-RED executado sobre o ambiente Node.js.

Módulos do Node-RED: node-red-node-serialport para controle de fluxo serial e node-red-dashboard para construção da interface gráfica.

Processo de Montagem, Integração e Execução
Montagem do Hardware na Protoboard
Para a alimentação do circuito, o pino 5V do Arduino é conectado à linha positiva da protoboard e o pino GND à linha negativa da protoboard.

O leitor RFID MFRC522 tem seus pinos conectados diretamente ao Arduino seguindo o barramento SPI padrão, onde o SDA vai para o Pino Digital 10, SCK para o Pino Digital 13, MOSI para o Pino Digital 11, MISO para o Pino Digital 12, GND para a linha negativa da protoboard, RST para o Pino Digital 9 e o pino 3.3V conectado obrigatoriamente na saída 3.3V do Arduino para evitar a queima do componente.

O LED Verde e o LED Vermelho são posicionados na protoboard com seus terminais mais curtos (Catodo) conectados na linha negativa. Os terminais mais longos (Anodo) recebem resistores de 220Ω em série, sendo que o resistor do LED Verde é associado ao Pino Digital 7 e o do LED Vermelho ao Pino Digital 6 do Arduino.

O buzzer ativo é inserido na protoboard com o terminal negativo na linha comum de GND e o terminal positivo em série com um resistor de 220Ω conectado ao Pino Digital 8 do Arduino para proteção contra picos de corrente.

Configuração e Upload do Firmware
Com o Node-RED inicialmente fechado para evitar conflitos na porta serial, a biblioteca MFRC522 deve estar instalada na Arduino IDE através do Gerenciador de Bibliotecas. O Arduino é conectado ao computador via cabo USB, selecionando o modelo correspondente e a respectiva porta COM ativa. O código C++ do firmware é carregado na placa. O Serial Monitor pode ser utilizado de forma isolada para validação preliminar da leitura física dos cartões e fechado em seguida.

Configuração do Servidor Back-end (Node-RED)
O servidor é inicializado via terminal e o editor local é acessado pelo navegador. Na gerência de paletas, verifica-se a instalação dos nós de comunicação serial e de dashboard. Após a importação do JSON com a lógica de fluxo, o nó de entrada serial é configurado com a mesma porta COM utilizada pelo Arduino sob a velocidade de 9600 Baud. O nó de atraso adjacente é parametrizado em modo Rate Limit para filtrar o fluxo de entrada, permitindo apenas uma mensagem a cada 3 segundos e descartando qualquer leitura intermediária repetida. O fluxo se torna ativo após a execução do Deploy.

Operação e Validação do Fluxo
A interface gráfica de usuário é acessada pelo navegador no endereço de Dashboard local.

Durante o teste de acesso liberado, a aproximação do chaveiro do profissional ativo envia os bytes correspondentes via barramento serial. O Node-RED interpreta os dados, gera uma query SQL simulada para a tabela de veterinários e renderiza na Dashboard os dados do paciente e a medicação associada. Como resposta ao hardware, o fluxo envia um comando que ativa o LED Verde e gera um bipe de confirmação no buzzer da protoboard.

No teste de bloqueio, a aproximação do cartão do profissional suspenso faz com que o Node-RED intercepte a string, trave a emissão de documentos na interface web com um aviso de erro e envie o comando para que o Arduino pisque o LED Vermelho e emita três bipes de alerta sonoro. O filtro de taxa de mensagens garante que o comportamento contínuo do leitor não gere instabilidade de memória ou oscilações no painel de telemedicina.
