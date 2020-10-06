FROM gcc:10
WORKDIR /
COPY ./* ./
RUN g++ cxylex.cpp -o program
RUN chmod +x program