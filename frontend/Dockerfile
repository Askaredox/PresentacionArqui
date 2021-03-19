FROM node:12 as build-step
RUN mkdir /app
WORKDIR /app
COPY package.json /app
RUN npm install 
COPY . /app
RUN npm run build

FROM nginx
COPY ./default.conf /etc/nginx/conf.d/default.conf
COPY --from=build-step /app/build /usr/share/nginx/html