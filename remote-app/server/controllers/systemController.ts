import expressAsyncHandler from "express-async-handler";
import mqtt from "mqtt";

const runningApps = expressAsyncHandler(async (req, res) => {
  const client = mqtt.connect("http://0.0.0.0:1883");
  client.on("connect", () => {
    console.log("Connect to mqtt!");

    client.subscribe("temperature", (err) => {
      if (err) {
        console.error("Subscribe error:", err);
      }
    });
  });

  let message = "Waiting data ...";
  client.on("message", (topic, payload) => {
    console.log(topic);
    console.log(payload.toString());
    message = payload.toString();
    res.json(message);
    client.end();
  });

  client.on("error", (err) => {
    console.error("Client error:", err);
  });
});

const getApp = expressAsyncHandler(async (req, res) => {
  console.log(req.params.name);
  console.log(req.query.name);
  let name: any = req.query.name;

  const client = mqtt.connect("http://0.0.0.0:1883");
  client.on("connect", () => {
    console.log("Connect to mqtt!");

    client.subscribe(name, (err) => {
      if (err) {
        console.error("Subscribe error:", err);
      }
    });
  });

  let message = "Waiting data ...";
  client.on("message", (topic, payload) => {
    console.log(topic);
    console.log(payload.toString());
    message = payload.toString();
    res.json(message);
    client.end();
  });

  client.on("error", (err) => {
    console.error("Client error:", err);
  });
});

export default { runningApps, getApp };
