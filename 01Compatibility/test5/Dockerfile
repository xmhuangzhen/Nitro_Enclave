FROM node:14

WORKDIR /

COPY package*.json test5.js ./

RUN npm install

EXPOSE 3000

CMD ["node", "test5.js"]