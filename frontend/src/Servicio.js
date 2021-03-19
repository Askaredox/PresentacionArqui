export class Servicio{
    static async fetch(){
        const url = "http://13.58.130.210:5000"
        //const url = "http://172.19.0.3:5000";
        const response = await fetch(url + "/getState");
        const data = await response.json();

        const date = new Date();
        const hh = date.getHours().toString();
        const mm = date.getMinutes().toString();
        const ss = date.getSeconds().toString();
        return { name: `${hh}:${mm}:${ss}`, data: data.analogo};
    }
}