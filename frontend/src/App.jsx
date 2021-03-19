import './App.css';
import { LineChart, Line, CartesianGrid, XAxis, YAxis, Legend } from 'recharts';
import { Servicio } from "./Servicio";

class App extends React.Component {
  constructor(){
    super();
    this.state = {
      analogo=[
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
        { name: '00:00:00', data: 0 },
      ]
    };
    this.intervalo = setInterval(this.getData, 5000);
  }

  componentWillUnmount() {
    clearInterval(this.intervalo);
  }

  render() {
    return (
      <div className='Graphs'>
        <h1>Graficas</h1>
        <h3>Datos</h3>
        <LineChart width={600} height={300} data={this.state.analogo} margin={{ top: 5, right: 20, bottom: 5, left: 0 }}>
          <Line type="monotone" dataKey="data" stroke="#8884d8" isAnimationActive={false} />
          <CartesianGrid stroke="#ccc" strokeDasharray="5 5" />
          <Legend />
          <XAxis dataKey="name" />
          <YAxis />
        </LineChart>
      </div>
    );
  }

  getData = () => {
    let datos = this.state.analogo;
    datos = datos1.slice(1);

    Servicio.fetch().then(value => {
        datos.push(value);
        this.setState({ analogo: datos })
    });
  }
}

export default App;
