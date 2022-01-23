FROM amazonlinux

WORKDIR /

COPY test2.c ./

RUN yum install gcc net-tools -y

RUN gcc -o test2 test2.c

CMD ["/test2"]