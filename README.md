# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- Linus Lei
- Way Zheng

## Lab Question Answers

Answer for Question 1: 

Question 1: How did the reliability of UDP change when you added 50% loss to your local environment? Why did this occur?

-I sent 1 to 10 but the server only received 2,3,7,9;
-I sent 1 to 10 again but the server only received 3,4,6,9,10.
-what happend: some of the contents are lost during the transission;
-why did this occur: UTP is only responsible for sending packets, and it wouln't detect the lost packages. as there’s no error control mechanism in UDP, it simply discards the packet as soon as an error is detected. Furthermore, transmitting a lot of data using UDP may cause congestion in a network.  

Question 2: How did the reliability of TCP change? Why did this occur?

-The server received all the stuff, having a good reliability. This is because TCP ensures that data is not damaged, lost, duplicated, or delivered out of order to a receiving process. 

Question 3: How did the speed of the TCP response change? Why might this happen?

-If I type in the numbers really quick, then the TCP response time would be much longer. Becuase TCP is always waiting for the previous package to be received before sneding the new one, and if it didn't receive it would do it again. That's why the resposne time increases.

