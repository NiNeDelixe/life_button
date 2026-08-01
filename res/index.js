const modeSelect = document.getElementById("mode");
const settingsDiv = document.getElementById("settings");

modeSelect.addEventListener("change", loadSettings);

function loadModes() {
    fetch("/modes")
        .then(r => r.json())
        .then(modes => {
            modeSelect.innerHTML = "";

            modes.forEach(mode => {
                const option = document.createElement("option");
                option.value = mode.id;
                option.textContent = mode.name;
                modeSelect.appendChild(option);
            });

            loadSettings();
        });
}

function loadSettings() {
    fetch("/mode?type=" + modeSelect.value)
        .then(r => r.json())
        .then(data => {

            settingsDiv.innerHTML = "";

            data.forEach(setting => {

                const block = document.createElement("div");
                block.className = "setting";

                switch (setting.type) {

                    case "bool": {

                        block.classList.add("checkbox");

                        const label = document.createElement("label");
                        label.textContent = setting.name;

                        const input = document.createElement("input");
                        input.type = "checkbox";
                        input.id = setting.name;
                        input.dataset.type = "bool";
                        input.checked = setting.value;

                        block.appendChild(label);
                        block.appendChild(input);

                        break;
                    }

                    case "array": {

                        const label = document.createElement("label");
                        label.textContent = setting.name;
                        block.appendChild(label);

                        const container = document.createElement("div");
                        container.id = setting.name;
                        container.dataset.type = "array";

                        setting.value.forEach(value => {
                            container.appendChild(createArrayInput(value));
                        });

                        const buttons = document.createElement("div");
                        buttons.className = "array-buttons";

                        const add = document.createElement("button");
                        add.type = "button";
                        add.textContent = "+";

                        add.onclick = () => {
                            container.appendChild(createArrayInput(""));
                        };

                        buttons.appendChild(add);

                        block.appendChild(container);
                        block.appendChild(buttons);

                        break;
                    }

                    default: {

                        const label = document.createElement("label");
                        label.textContent = setting.name;

                        const input = document.createElement("input");
                        input.type = "number";
                        input.id = setting.name;
                        input.dataset.type = "int";
                        input.value = setting.value;

                        block.appendChild(label);
                        block.appendChild(input);
                    }

                }

                settingsDiv.appendChild(block);

            });

        });
}

function createArrayInput(value) {

    const row = document.createElement("div");
    row.className = "array-item";

    const input = document.createElement("input");
    input.type = "text";
    input.value = value;

    const remove = document.createElement("button");
    remove.type = "button";
    remove.textContent = "-";

    remove.onclick = () => row.remove();

    row.appendChild(input);
    row.appendChild(remove);

    return row;
}

function save() {

    const params = new URLSearchParams();
    params.append("type", modeSelect.value);

    document.querySelectorAll("#settings input[data-type]").forEach(input => {

        switch (input.dataset.type) {

            case "bool":
                params.append(input.id, input.checked);
                break;

            case "int":
                params.append(input.id, input.value);
                break;

        }

    });

    document.querySelectorAll("[data-type=array]").forEach(container => {

        const values = [];

        container.querySelectorAll("input").forEach(input => {
            values.push(input.value);
        });

        params.append(container.id, values.join(","));
    });

    fetch("/setMode?" + params.toString());
}

function restart() {
    fetch("/restart");
}

function register() {
    fetch("/api/koth/register/toggle", {
        method: "POST"
    });
}

loadModes();