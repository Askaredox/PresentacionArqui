from flask import Flask, json, request
from flask_cors import CORS
from database import Database

app = Flask(__name__)
cors = CORS(app, resources={r"/api/*": {"origin": "*"}})
db = Database()


@app.route('/')
def todo_good():
    return 'todo good'


@app.route('/getState', methods=['GET'])
def getState():
    ret = db.getData()
    ret['ok'] = True
    return json.dumps(ret)


@app.route('/setEncendido', methods=['GET'])
def setEncendido():
    val = request.args.get('val')
    newVal = db.setEncendido(val)
    ret = None
    if newVal is None:
        ret = {'ok': False}
    else:
        ret = {'ok': True, 'newVal': newVal}
    return json.dumps(ret)

@app.route('/setAnalogo', methods=['GET'])
def setAnalogo():
    val = request.args.get('val')
    newVal = db.setAnalogo(val)
    ret = None
    if newVal is None:
        ret = {'ok': False}
    else:
        ret = {'ok': True, 'newVal': newVal}
    return json.dumps(ret)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, threaded=True)
