FROM amazonlinux

WORKDIR /

COPY test1.cpp ./

RUN yum install python3 net-tools -y

RUN yum install gcc-c++ -y

RUN g++ -o test1 test1.cpp

CMD ["/test1"]