
[![My Skills](https://skills.thijs.gg/icons?i=c,linux,git)](https://skills.thijs.gg)
# Threads-Synchronization
### ***Overview:***
This project was coded as a part of the operation curse in the 2nd semester of my 2nd year at BIU.<br>
This project was coded in multiple threads on C.<br>
The project implements a solution for the producer-consumer problem.<br>
The producer-Consumer problem is a classical synchronization problem in the operating system.<br>
With the presence of more than one process and limited resources in the system the synchronization problem arises.<br>
If one resource is shared between more than one process simultaneously, it can lead to data inconsistency.<br>
### ***About:***
The overall scenario simulated news broadcasting. Different types of stories(3 types) are produced and the system sorts them and displays them to the public.<br>
In this project, the ‘new stories’ are simulated by simple strings which should be displayed on the screen in the order they arrive.<br><br>
***The simulation involves four types of active actors:*** <br>
**1. Producer:** Each producer creates news stories with a specific format.<br>
They pass their information to the Dispatcher via a private queue.<br>
After inserting all products, they send a "DONE" message through their queue.<br>
**2. Dispatcher:** The Dispatcher accepts messages from the Producers and sorts them based on type.<br>
It uses a Round Robin algorithm to scan the Producers' queues.<br>
Once all Producers are done, it sends a "DONE" message through each of its queues.<br>
**3. Co-Editor:** Co-Editors receive sorted messages from the Dispatcher, "edit" them, and pass them to the Screen Manager via a shared queue.
The editing process includes a simulated delay.<br>
**4. Screen Manager:** The Screen Manager displays messages received from the Co-Editors on the screen.<br>
After printing all messages and receiving three "DONE" messages, it displays a 'DONE' statement.<br><br>
### ***System Design:***
The system architecture involves communication between different components:<br>
* Producers communicate with the Dispatcher via their Producer queues.<br>
* The Dispatcher communicates with Co-Editors via queues for each message type.<br>
* Co-Editors communicate with the Screen Manager via a shared queue.<br><br>
### ***Running the project:***
1. Clone the project to your machine.<br>
2. write the `make` command line.<br>
3. write `./ex3.out config.txt`<br>
when the config.txt is txt  file that contains all the articles.
##***Dependencies:***
* Linux
* Git

