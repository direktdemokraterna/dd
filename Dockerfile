# Usage
# docker build -t dd/dd_web_image .
# docker run --name dd_web -d -p 80:80 -p 3306:3306 dd/dd_web_image

FROM tutum/lamp

RUN apt-get update && apt-get install -y \
    php5-curl \
    php5-gd

COPY . /app
COPY docker /
WORKDIR /app

EXPOSE 80 3306
CMD ["/run.sh"]
