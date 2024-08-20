async function listApps() {
  axios
    .get("http://0.0.0.0:3000/apps")
    .then((res) => {
      console.log(res);
      const result = [];
      res.data.forEach((el) => {
        result.push(el);
      });
      document.getElementById("apps").appendChild(createTable(result));
    })
    .catch((err) => {
      console.log(err);
    });
}

function searchApp() {
  let name = document.getElementById("searchAppName").selectedOptions[0].text;
  console.log("send msg " + name + "!");

  axios
    .get("http://0.0.0.0:3000/app", {
      params: {
        name: name.toLowerCase(),
      },
    })
    .then((res) => {
      console.log(res);
      document.getElementById("app").innerHTML = `Data: ${res.data}`;
    })
    .catch((err) => {
      console.log(err);
    });
}

function createApp() {
  let name = document.getElementById("appName").selectedOptions[0].value;

  axios
    .post("http://0.0.0.0:3000/add", {
      name,
    })
    .then(() => {
      listItems();
    })
    .catch((err) => {
      console.log(err);
    });
}

function createTable(data) {
  const table = document.createElement("table");
  table.setAttribute("border", "1");

  const headerRow = document.createElement("tr");
  Object.keys(data[0]).forEach((key) => {
    const th = document.createElement("th");
    th.appendChild(document.createTextNode(key));
    headerRow.appendChild(th);
  });
  table.appendChild(headerRow);

  data.forEach((item) => {
    const row = document.createElement("tr");
    Object.values(item).forEach((value) => {
      const td = document.createElement("td");
      td.appendChild(document.createTextNode(value));
      row.appendChild(td);
    });
    table.appendChild(row);
  });

  return table;
}
