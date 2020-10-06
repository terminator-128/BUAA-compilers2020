# 这是一个简单的Dockerfile配置文件
FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc cxylex.cpp -lstdc++ -o program
RUN chmod +x program
