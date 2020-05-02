# -*- coding:utf8 -*-
import random
from flask import Flask, request

app = Flask("smartcar-endpoint")


@app.route('/gyro', methods=['GET'])
def gyroscope_endpoint():
    return str(random.randint(0, 359))


@app.route('/drive', methods=['GET'])
def drive_endpoint():
    speed = request.args.get('speed')
    angle = request.args.get('angle')
    if speed:
        print("setSpeed(%s)" % speed)
    if angle:
        print("setAngle(%s)" % angle)
    return "ok"


def main():
    random.seed()
    app.run()


if __name__ == '__main__':
    main()
