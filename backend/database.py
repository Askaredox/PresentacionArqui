class Database:
    def __init__(self) -> None:
        self.encendido = False
        self.analogo = 0

    def getData(self):
        return {'encendido':self.encendido, 'analogo':self.analogo}

    def setEncendido(self, val):
        nval = bool(val)
        if type(nval) == type(True):
            self.encendido = nval
            return nval
        else:
            return None

    def setAnalogo(self, val):
        nval = int(val)/1024
        if type(nval) == type(0.1):
            self.analogo = nval
            return nval
        else:
            return None
