"use strict";

/* =========================================================
   1. LOCATION DATA
   ========================================================= */

const locations = [
  ["J1", "Clock Tower Chowk"],
  ["J2", "Prince Chowk"],
  ["J3", "Saharanpur Chowk"],
  ["J4", "Balliwala Chowk"],
  ["J5", "Karghi Chowk"],
  ["J6", "Vidhan Sabha Twin Junction"],
  ["J7", "ISBT Chowk"],
  ["J8", "Bindal River Junction"],
  ["J9", "Jogiwala Chowk"],
  ["J10", "Araghar Junction"],
  ["J11", "Ballupur Chowk"],
  ["J12", "Ashley Hall Junction"],
  ["J13", "Kishan Nagar Junction"],
  ["J14", "Sahastradhara Crossing"],
  ["J15", "Employment Office Crossing"],

  ["H1", "Doon Hospital"],
  ["H2", "Shri Mahant Indiresh Hospital"],
  ["H3", "Max Super Speciality Hospital"],
  ["H4", "Graphic Era Hospital"],
  ["H5", "Synergy Hospital"],
  ["H6", "Coronation Hospital"],
  ["H7", "Combined Medical Institute"],
  ["H8", "Prem Sukh Hospital"],
  ["H9", "Uttaranchal Hospital"],

  ["P1", "Dalanwala Police Station"],
  ["P2", "Nehru Colony Police Station"],
  ["P3", "Patel Nagar Police Station"],
  ["P4", "Rajpur Police Station"],
  ["P5", "Clement Town Police Station"],

  ["F1", "Dehradun Fire Station"],
  ["F2", "Doiwala Fire Station"],
  ["F3", "Selaqui Fire Station"],
  ["F4", "Mussoorie Fire Station"],

  ["R1", "Dehradun Central Emergency Rescue Hub"],
  ["R2", "Saharanpur Chowk Emergency Rescue Hub"]
];

const names = Object.fromEntries(locations);

const mapNames = {
  J1: "Clock Tower",
  J2: "Prince Chowk",
  J3: "Saharanpur",
  J4: "Balliwala",
  J5: "Karghi Chowk",
  J6: "Vidhan Sabha",
  J7: "ISBT",
  J8: "Bindal River",
  J9: "Jogiwala",
  J10: "Araghar",
  J11: "Ballupur",
  J12: "Ashley Hall",
  J13: "Kishan Nagar",
  J14: "Sahastradhara",
  J15: "Employment Office",
  H1: "Doon Hospital",
  H2: "Mahant Indiresh",
  H3: "Max Hospital",
  H4: "Graphic Era",
  H5: "Synergy Hospital",
  H6: "Coronation",
  H7: "Combined Medical",
  H8: "Prem Sukh",
  H9: "Uttaranchal",
  P1: "Dalanwala PS",
  P2: "Nehru Colony PS",
  P3: "Patel Nagar PS",
  P4: "Rajpur PS",
  P5: "Clement Town PS",
  F1: "Dehradun Fire",
  F2: "Doiwala Fire",
  F3: "Selaqui Fire",
  F4: "Mussoorie Fire",
  R1: "Central Rescue",
  R2: "Saharanpur Rescue"
};


/* =========================================================
   2. ROAD DATA
   [location A, location B, distance, speed limit,
    capacity, current vehicles]

   Total: 70 roads
   Horizontal: 30 | Vertical: 28 | Diagonal: 12
   ========================================================= */

const roads = [

  // HORIZONTAL ROADS (30)

  ["J1", "H1", 3, 30, 60, 25],
  ["H1", "P1", 4, 35, 80, 45],
  ["P1", "J2", 5, 40, 100, 65],
  ["J2", "H2", 3, 30, 60, 52],
  ["H2", "F1", 6, 40, 100, 90],
  ["F1", "J3", 4, 35, 80, 30],

  ["H6", "J4", 5, 40, 100, 75],
  ["J4", "R1", 3, 30, 60, 18],
  ["R1", "H3", 4, 35, 80, 70],
  ["H3", "J5", 6, 40, 100, 95],
  ["J5", "P2", 3, 30, 60, 48],
  ["P2", "F2", 5, 40, 100, 55],

  ["P4", "H4", 4, 35, 80, 25],
  ["H4", "J6", 5, 40, 100, 82],
  ["J6", "P3", 3, 30, 60, 58],
  ["P3", "H7", 6, 40, 100, 35],
  ["H7", "R2", 4, 35, 80, 72],
  ["R2", "J7", 5, 40, 100, 105],

  ["F4", "J8", 3, 30, 60, 20],
  ["J8", "H5", 6, 40, 100, 88],
  ["H5", "J9", 4, 35, 80, 42],
  ["J9", "P5", 5, 40, 100, 98],
  ["P5", "H8", 3, 30, 60, 55],
  ["H8", "J10", 7, 40, 100, 35],

  ["J11", "H9", 4, 35, 80, 60],
  ["H9", "J12", 5, 40, 100, 25],
  ["J12", "J13", 6, 40, 100, 20],
  ["J13", "J14", 7, 30, 80, 70],
  ["J14", "J15", 5, 40, 100, 50],
  ["J15", "F3", 4, 35, 80, 90],


  // VERTICAL ROADS (28)

  ["J1", "H6", 5, 40, 100, 40],
  ["H6", "P4", 4, 35, 80, 65],
  ["P4", "F4", 6, 40, 100, 85],
  ["F4", "J11", 3, 30, 60, 30],

  ["H1", "J4", 4, 35, 80, 55],
  ["J4", "H4", 5, 40, 100, 95],
  ["H4", "J8", 3, 30, 60, 15],
  ["J8", "H9", 6, 40, 100, 75],

  ["P1", "R1", 3, 30, 60, 35],
  ["R1", "J6", 5, 40, 100, 60],
  ["J6", "H5", 4, 35, 80, 78],
  ["H5", "J12", 7, 40, 100, 110],

  ["J2", "H3", 4, 35, 80, 45],
  ["H3", "P3", 5, 40, 100, 80],
  ["P3", "J9", 3, 30, 60, 50],
  ["J9", "J13", 6, 40, 100, 92],

  ["H2", "J5", 5, 40, 100, 30],
  ["J5", "H7", 4, 35, 80, 62],
  ["H7", "P5", 6, 40, 100, 100],
  ["P5", "J14", 3, 30, 60, 25],

  ["F1", "P2", 4, 35, 80, 70],
  ["P2", "R2", 5, 40, 100, 40],
  ["R2", "H8", 3, 30, 60, 58],
  ["H8", "J15", 6, 40, 100, 85],

  ["J3", "F2", 5, 40, 100, 65],
  ["F2", "J7", 4, 35, 80, 20],
  ["J7", "J10", 7, 40, 100, 95],
  ["J10", "F3", 3, 30, 60, 42],


  // DIAGONAL ROADS (12)

  ["J1", "J4", 6, 40, 100, 45],
  ["J4", "J6", 4, 35, 80, 75],
  ["H2", "P2", 5, 40, 100, 55],
  ["H3", "J3", 3, 30, 60, 35],
  ["J5", "R2", 6, 40, 100, 105],
  ["P4", "J8", 4, 35, 80, 50],
  ["J6", "J9", 5, 40, 100, 85],
  ["J6", "H3", 3, 30, 60, 65],
  ["P2", "J7", 7, 40, 100, 95],
  ["J8", "J12", 5, 35, 80, 30],
  ["J9", "J14", 6, 40, 100, 72],
  ["F4", "H9", 4, 30, 60, 55]
];


/* =========================================================
   3. VEHICLE SPEEDS
   ========================================================= */

const speeds = {
  "Car": 40,
  "Truck": 30,
  "Bus": 35,
  "Ambulance": 50,
  "Fire Truck": 40,
  "Police Van": 45,
  "Bike": 35,
  "Bicycle": 15
};


/* =========================================================
   4. COLORS AND HELPERS
   ========================================================= */

const colors = {
  low: "#35d39a",
  moderate: "#f4c95d",
  high: "#ff9b55",
  full: "#ff5268",
  route: "#26ff91",
  unknown: "#71849b"
};

const $ = id => document.getElementById(id);
const SVG_NS = "http://www.w3.org/2000/svg";


/* =========================================================
   5. CONGESTION CALCULATION
   ========================================================= */

function congestionPercent(road) {
  return (road[5] / road[4]) * 100;
}

function congestionLevel(road) {
  const percentage = congestionPercent(road);

  if (percentage < 50) return "low";
  if (percentage < 80) return "moderate";
  if (percentage < 100) return "high";

  return "full";
}


// Congestion-aware speed calculation.
// Uses the same road speed limits as the C++ module.

function getEffectiveSpeed(road, vehicleType) {
  const roadSpeedLimit = road[3];

  const vehiclePreferredSpeed =
    speeds[vehicleType] || 40;

  let speed = Math.min(
    roadSpeedLimit,
    vehiclePreferredSpeed
  );

  const congestion = congestionPercent(road);

  if (congestion >= 100) {
    speed *= 0.40;
  } else if (congestion >= 80) {
    speed *= 0.60;
  } else if (congestion >= 50) {
    speed *= 0.80;
  }

  return Math.max(speed, 5.0);
}


function getRoad(a, b) {
  return roads.find(road =>
    (road[0] === a && road[1] === b) ||
    (road[0] === b && road[1] === a)
  );
}


function trafficColor(a, b) {
  const road = getRoad(a, b);

  if (!road) return colors.unknown;

  return colors[congestionLevel(road)];
}


/* =========================================================
   6. POPULATE LOCATION DROPDOWNS
   ========================================================= */

function fillLocationSelect(id, selectedValue) {
  const select = $(id);

  if (!select) return;

  select.replaceChildren();

  locations.forEach(([code, name]) => {
    const option = document.createElement("option");

    option.value = code;
    option.textContent = `${code} - ${name}`;

    select.appendChild(option);
  });

  select.value = selectedValue;
}

fillLocationSelect("source", "J1");
fillLocationSelect("destination", "J15");
fillLocationSelect("modalSource", "J1");
fillLocationSelect("modalDestination", "J15");


/* =========================================================
   7. TRAFFIC SUMMARY
   ========================================================= */

function updateTrafficSummary() {
  const counts = {
    low: 0,
    moderate: 0,
    high: 0,
    full: 0
  };

  roads.forEach(road => {
    counts[congestionLevel(road)]++;
  });

  $("lowCount").textContent = counts.low;
  $("moderateCount").textContent = counts.moderate;
  $("highCount").textContent = counts.high;
  $("fullCount").textContent = counts.full;
  $("roadCount").textContent = roads.length;

  const highestCount = Object.entries(counts)
    .sort((a, b) => b[1] - a[1])[0][0];

  const trafficLabels = {
    low: "Low",
    moderate: "Moderate",
    high: "High",
    full: "Heavy"
  };

  $("overallTraffic").textContent =
    trafficLabels[highestCount];

  $("overallTraffic").className =
    highestCount === "low" ? "green" :
    highestCount === "moderate" ? "yellow" : "";
}


// Simulate vehicles travelling on the selected road segments
function addTrafficToRoute(routeSegments, vehicleCount = 1) {
  routeSegments.forEach(road => {
    road[5] += vehicleCount * 5;
  });

  updateTrafficSummary();
}


updateTrafficSummary();


/* =========================================================
   8. MAP NODE POSITIONS
   ========================================================= */

const grid = [
  ["J1", "H1", "P1", "J2", "H2", "F1", "J3"],
  ["H6", "J4", "R1", "H3", "J5", "P2", "F2"],
  ["P4", "H4", "J6", "P3", "H7", "R2", "J7"],
  ["F4", "J8", "H5", "J9", "P5", "H8", "J10"],
  ["J11", "H9", "J12", "J13", "J14", "J15", "F3"]
];

const positions = {};

const MAP_X = 75;
const MAP_Y = 75;
const COL_GAP = 125;
const ROW_GAP = 125;

grid.forEach((row, rowIndex) => {
  row.forEach((id, colIndex) => {
    if (!id) return;

    positions[id] = {
      x: MAP_X + colIndex * COL_GAP,
      y: MAP_Y + rowIndex * ROW_GAP
    };
  });
});


/* =========================================================
   9. MAP CONNECTIONS
   ========================================================= */

const mapEdges = roads.map(([a, b]) => [a, b]);


/* =========================================================
   10. SVG HELPER
   ========================================================= */

function makeSvg(tag, attributes = {}) {
  const element = document.createElementNS(
    SVG_NS,
    tag
  );

  Object.entries(attributes).forEach(([key, value]) => {
    element.setAttribute(key, String(value));
  });

  return element;
}

/* =========================================================
   11. DRAW NETWORK MAP
   ========================================================= */

function drawNetwork(routePath = []) {
  // Accept either one route or multiple routes
  const routePaths = Array.isArray(routePath[0])
    ? routePath
    : [routePath];

  const allRouteNodes = new Set(routePaths.flat());
  const svg = $("networkSvg");

  if (!svg) return;

  svg.replaceChildren();

  svg.setAttribute("viewBox", "0 0 900 650");
  svg.setAttribute("preserveAspectRatio", "xMidYMid meet");

  // Background
  svg.appendChild(makeSvg("rect", {
    x: 0,
    y: 0,
    width: 900,
    height: 650,
    fill: "#071727"
  }));

  // Grid lines
  for (let x = 0; x <= 900; x += 25) {
    svg.appendChild(makeSvg("line", {
      x1: x,
      y1: 0,
      x2: x,
      y2: 650,
      stroke: "#193044",
      "stroke-width": 1,
      opacity: 0.6
    }));
  }

  for (let y = 0; y <= 650; y += 25) {
    svg.appendChild(makeSvg("line", {
      x1: 0,
      y1: y,
      x2: 900,
      y2: y,
      stroke: "#193044",
      "stroke-width": 1,
      opacity: 0.6
    }));
  }

  // City blocks
  for (let r = 0; r < 5; r++) {
    for (let c = 0; c < 7; c++) {
      svg.appendChild(makeSvg("rect", {
        x: 22 + c * 125,
        y: 22 + r * 125,
        width: 88,
        height: 70,
        rx: 3,
        fill: "#102c39",
        opacity: 0.4
      }));
    }
  }

  // Selected connections from ALL emergency routes
  const selectedEdges = new Set();

  routePaths.forEach(path => {
    for (let i = 0; i < path.length - 1; i++) {
      const a = path[i];
      const b = path[i + 1];

      selectedEdges.add(`${a}|${b}`);
      selectedEdges.add(`${b}|${a}`);
    }
  });

  // Road casings
  mapEdges.forEach(([a, b]) => {
    const p = positions[a];
    const q = positions[b];

    if (!p || !q) return;

    svg.appendChild(makeSvg("line", {
      x1: p.x,
      y1: p.y,
      x2: q.x,
      y2: q.y,
      stroke: "#174a82",
      "stroke-width": 10,
      "stroke-linecap": "round"
    }));
  });

  // All roads blue; selected route uses congestion colours
  mapEdges.forEach(([a, b]) => {
    const p = positions[a];
    const q = positions[b];

    if (!p || !q) return;

    const selected = selectedEdges.has(`${a}|${b}`);
    const road = getRoad(a, b);

    const color = selected
      ? trafficColor(a, b)
      : "#238BFF";

    const line = makeSvg("line", {
      x1: p.x,
      y1: p.y,
      x2: q.x,
      y2: q.y,
      stroke: color,
      "stroke-width": selected ? 7 : 4,
      "stroke-linecap": "round",
      opacity: 1
    });

    if (selected) {
      line.style.filter =
        `drop-shadow(0 0 6px ${color})`;
    }

    const title = makeSvg("title");

    if (road) {
      const percentage =
        Math.round(congestionPercent(road));

      const status =
        congestionLevel(road).toUpperCase();

      title.textContent =
        `${a} (${names[a]}) ↔ ${b} (${names[b]}) | ` +
        `${road[2]} km | ${road[5]}/${road[4]} vehicles | ` +
        `${percentage}% congestion | ${status}` +
        (selected ? " | SELECTED ROUTE" : "");
    } else {
      title.textContent =
        `${a} (${names[a]}) ↔ ${b} (${names[b]})`;
    }

    line.appendChild(title);
    svg.appendChild(line);
  });

  // Draw route links not already in schematic map
  routePaths.forEach(routePath => {
  for (let i = 0; i < routePath.length - 1; i++) {
    const a = routePath[i];
    const b = routePath[i + 1];

    const alreadyDrawn = mapEdges.some(edge =>
      (edge[0] === a && edge[1] === b) ||
      (edge[0] === b && edge[1] === a)
    );

    if (alreadyDrawn) continue;

    const p = positions[a];
    const q = positions[b];

    if (!p || !q) continue;

    const road = getRoad(a, b);
    const color = road ? trafficColor(a, b) : "#238BFF";

    const line = makeSvg("line", {
      x1: p.x,
      y1: p.y,
      x2: q.x,
      y2: q.y,
      stroke: color,
      "stroke-width": 7,
      "stroke-linecap": "round",
      "stroke-dasharray": "8 5"
    });

    line.style.filter = `drop-shadow(0 0 6px ${color})`;

    const title = makeSvg("title");
    title.textContent = `${a} ↔ ${b} | Selected connection`;

    line.appendChild(title);
    svg.appendChild(line);
  }
});

  // Draw location nodes
  locations.forEach(([id, fullName]) => {
    const p = positions[id];

    if (!p) return;

    const type = id[0];
    const onRoute = allRouteNodes.has(id);

    const nodeColor =
      type === "H" ? "#ff5268" :
      type === "P" ? "#398cff" :
      type === "F" ? "#ff9c35" :
      type === "R" ? "#38ef85" :
      "#d9e7f7";

    const group = makeSvg("g");

    group.appendChild(makeSvg("circle", {
      cx: p.x,
      cy: p.y,
      r: onRoute ? 12 : 10,
      fill: "#07111f",
      stroke: onRoute ? "#238BFF" : nodeColor,
      "stroke-width": onRoute ? 4 : 3
    }));

    group.appendChild(makeSvg("circle", {
      cx: p.x,
      cy: p.y,
      r: 4.5,
      fill: onRoute ? "#238BFF" : nodeColor
    }));

    const code = makeSvg("text", {
      x: p.x,
      y: p.y + 22,
      class: "map-node-code"
    });

    code.textContent = id;
    group.appendChild(code);

    const label = makeSvg("text", {
      x: p.x,
      y: p.y + 35,
      class: "map-node-name"
    });

    label.textContent = mapNames[id] || fullName;
    group.appendChild(label);

    const title = makeSvg("title");
    title.textContent = `${id} — ${fullName}`;

    group.appendChild(title);
    svg.appendChild(group);
  });

  // START and END markers for all routes
  routePaths.forEach((path, index) => {
    if (path.length === 0) return;

    const markers = [
      { id: path[0], text: `S${index + 1}`, color: "#22C55E" },
      {
        id: path[path.length - 1],
        text: `E${index + 1}`,
        color: "#EF4444"
      }
    ];

    markers.forEach(marker => {
      const p = positions[marker.id];
      if (!p) return;

      svg.appendChild(makeSvg("circle", {
        cx: p.x,
        cy: p.y,
        r: 12,
        fill: "none",
        stroke: marker.color,
        "stroke-width": 3
      }));

      const text = makeSvg("text", {
        x: p.x,
        y: p.y - 18,
        fill: marker.color,
        "font-size": 10,
        "font-weight": 700,
        "text-anchor": "middle",
        stroke: "#071727",
        "stroke-width": 2,
        "paint-order": "stroke"
      });

      text.textContent = marker.text;
      svg.appendChild(text);
    });
  });
}


// Draw map immediately
drawNetwork();


/* =========================================================
   12. DIJKSTRA'S ALGORITHM
   MINIMUM TRAVEL TIME ROUTING
   ========================================================= */

function calculateRoute(source, destination, vehicleType) {
  if (!names[source] || !names[destination]) {
    return null;
  }

  if (source === destination) {
    return null;
  }

  // Create graph
  const graph = Object.fromEntries(
    locations.map(([id]) => [id, []])
  );

  // Calculate travel time for each road
  roads.forEach(road => {
    const [a, b, km] = road;

    const effectiveSpeed =
      getEffectiveSpeed(road, vehicleType);

    const roadTime =
      (km / effectiveSpeed) * 60;

    graph[a].push({
      to: b,
      minutes: roadTime,
      road: road
    });

    graph[b].push({
      to: a,
      minutes: roadTime,
      road: road
    });
  });

  // Minimum travel time
  const minTime = Object.fromEntries(
    locations.map(([id]) => [id, Infinity])
  );

  const previous = {};
  const visited = new Set();

  minTime[source] = 0;

  // Dijkstra
  while (true) {
    let current = null;
    let bestTime = Infinity;

    for (const id of Object.keys(minTime)) {
      if (
        !visited.has(id) &&
        minTime[id] < bestTime
      ) {
        current = id;
        bestTime = minTime[id];
      }
    }

    if (current === null || current === destination) {
      break;
    }

    visited.add(current);

    graph[current].forEach(edge => {
      if (visited.has(edge.to)) return;

      const newTime =
        minTime[current] + edge.minutes;

      if (newTime < minTime[edge.to]) {
        minTime[edge.to] = newTime;

        previous[edge.to] = {
          from: current,
          road: edge.road
        };
      }
    });
  }

  // Check if destination is reachable
  if (!Number.isFinite(minTime[destination])) {
    return null;
  }

  // Reconstruct route
  const path = [destination];
  const segments = [];

  let current = destination;

  while (current !== source) {
    const step = previous[current];

    if (!step) return null;

    segments.unshift(step.road);

    current = step.from;
    path.unshift(current);
  }

  // Calculate total distance
  const totalDistance = segments.reduce(
    (sum, road) => sum + road[2],
    0
  );

  return {
    path: path,
    segments: segments,
    distance: totalDistance,
    minutes: minTime[destination]
  };
}


/* =========================================================
   13. DISPLAY ROUTE RESULTS
   ========================================================= */

function showRoute(
  source,
  destination,
  vehicleType,
  registration = "Demo vehicle",
  simulateTraffic = false
) {
  const error = $("plannerError");

  if (error) error.textContent = "";

  if (source === destination) {
    if (error) {
      error.textContent =
        "Choose different source and destination locations.";
    }
    return;
  }

  const result =
    calculateRoute(source, destination, vehicleType);

  if (!result) {
    if (error) error.textContent = "No route found.";
    return;
  }

  // Update simulated traffic only for newly added vehicles
  if (simulateTraffic) {
    addTrafficToRoute(result.segments, 1);
  }

  $("distance").innerHTML =
    `${result.distance.toFixed(1)} <em>km</em>`;

  $("time").innerHTML =
    `${Math.max(1, Math.round(result.minutes))} <em>min</em>`;

  $("segmentCount").textContent =
    result.segments.length;

  $("routeStatus").textContent =
    ["Ambulance", "Fire Truck", "Police Van"].includes(vehicleType)
      ? "PRIORITY ROUTE"
      : "ROUTE FOUND";

  $("routeSubtitle").textContent =
    `${registration} · ${vehicleType}`;

  // Display route path
  const routeResult = $("routeResult");
  routeResult.replaceChildren();

  const heading = document.createElement("b");
  heading.textContent = "Suggested path: ";
  routeResult.appendChild(heading);

  result.path.forEach((id, index) => {
    const chip = document.createElement("span");

    chip.className = "route-chip";
    chip.textContent = `${id} · ${names[id]}`;

    routeResult.appendChild(chip);

    if (index < result.path.length - 1) {
      routeResult.appendChild(
        document.createTextNode(" → ")
      );
    }
  });

  // Display traffic details for selected roads
  const details = $("segmentDetails");
  details.replaceChildren();

  const detailsTitle = document.createElement("b");
  detailsTitle.textContent = "Selected route segments";
  details.appendChild(detailsTitle);

  result.segments.forEach(road => {
    const [a, b, km, speedLimit, capacity, vehicles] = road;

    const status = congestionLevel(road);
    const percent = Math.round(congestionPercent(road));

    const row = document.createElement("div");
    row.className = "segment-item";

    const left = document.createElement("span");
    left.textContent =
      `${a} ↔ ${b} · ${km} km · ${speedLimit} km/h`;

    const right = document.createElement("span");

    right.textContent =
      `${status.toUpperCase()} (${vehicles}/${capacity}, ${percent}%)`;

    right.style.color = colors[status];

    row.append(left, right);
    details.appendChild(row);
  });

  // Highlight fastest route
  drawNetwork(result.path);
}


/* =========================================================
   DISPLAY ALL ASSIGNED EMERGENCY ROUTES
   ========================================================= */

function showEmergencyRoutes(vehicleAssignments) {
  if (!vehicleAssignments.length) return;

  const routeResult = $("routeResult");
  const details = $("segmentDetails");

  routeResult.replaceChildren();
  details.replaceChildren();

  let combinedDistance = 0;
  let fastestTime = Infinity;
  let allSegments = 0;

  // Route heading
  const heading = document.createElement("b");
  heading.textContent = "All assigned emergency routes:";
  routeResult.appendChild(heading);

  vehicleAssignments.forEach((item, index) => {
    const route = item.route;

    combinedDistance += route.distance;
    fastestTime = Math.min(fastestTime, route.minutes);
    allSegments += route.segments.length;

    // Display each assigned route
    const card = document.createElement("div");
    card.className = "emergency-route-item";

    const title = document.createElement("strong");
    title.textContent =
      `${item.vehicleType} · ${item.station.name} (${item.quantity})`;

    const path = document.createElement("p");
    path.textContent = route.path
      .map(id => `${id} · ${names[id]}`)
      .join(" → ");

    const info = document.createElement("p");
    info.textContent =
      `Distance: ${route.distance.toFixed(1)} km · ` +
      `Estimated time: ${Math.max(1, Math.round(route.minutes))} min`;

    card.append(title, path, info);
    routeResult.appendChild(card);
  });

  // Update route summary
  $("distance").innerHTML =
    `${combinedDistance.toFixed(1)} <em>km</em>`;

  $("time").innerHTML =
    `${Math.max(1, Math.round(fastestTime))} <em>min</em>`;

  $("segmentCount").textContent = allSegments;

  $("routeStatus").textContent = "EMERGENCY RESPONSE";

  $("routeSubtitle").textContent =
    `${vehicleAssignments.length} assigned response routes`;

  // Show traffic segments from every assigned route
  const detailsTitle = document.createElement("b");
  detailsTitle.textContent = "Traffic on assigned routes";
  details.appendChild(detailsTitle);

  vehicleAssignments.forEach(item => {
    const routeHeading = document.createElement("p");
    routeHeading.className = "emergency-segment-heading";
    routeHeading.textContent =
      `${item.vehicleType} · ${item.station.name}`;

    details.appendChild(routeHeading);

    item.route.segments.forEach(road => {
      const [a, b, km, speedLimit, capacity, vehicles] = road;

      const status = congestionLevel(road);
      const percent = Math.round(congestionPercent(road));

      const row = document.createElement("div");
      row.className = "segment-item";

      const left = document.createElement("span");
      left.textContent = `${a} ↔ ${b} · ${km} km`;

      const right = document.createElement("span");
      right.textContent =
        `${status.toUpperCase()} (${vehicles}/${capacity}, ${percent}%)`;

      right.style.color = colors[status];

      row.append(left, right);
      details.appendChild(row);
    });
  });

  // Keep the map focused on the fastest assigned route for now.
  const fastest = [...vehicleAssignments].sort(
    (a, b) => a.route.minutes - b.route.minutes
  )[0];

  drawNetwork(
  vehicleAssignments.map(item => item.route.path)
);
}



/* =========================================================
   14. FIND ROUTE BUTTON
   ========================================================= */

$("findRoute").addEventListener("click", () => {
  showRoute(
    $("source").value,
    $("destination").value,
    $("plannerVehicle").value
  );
});


/* =========================================================
   15. RESET ROUTE BUTTON
   ========================================================= */

$("resetMap").addEventListener("click", () => {
  drawNetwork();

  $("distance").innerHTML = "— <em>km</em>";
  $("time").innerHTML = "— <em>min</em>";
  $("segmentCount").textContent = "—";

  $("routeStatus").textContent = "AWAITING ROUTE";

  $("routeSubtitle").textContent =
    "Choose a source and destination to begin";

  $("routeResult").textContent =
    "Your suggested path will appear here after route calculation.";

  $("segmentDetails").innerHTML =
    "<b>Selected route segments</b>" +
    "<p>Calculate a route to see road traffic status.</p>";

  $("plannerError").textContent = "";
});


/* =========================================================
   16. VEHICLE FORM AND EMERGENCY MODAL
   ========================================================= */

function updateRegistrationField() {
  const isBicycle =
    $("vehicleType").value === "Bicycle";

  $("registrationGroup").style.display =
    isBicycle ? "none" : "block";

  $("registration").required = !isBicycle;
}


function openModal(isEmergency) {
  $("modalTitle").textContent =
    isEmergency ? "Add Emergency" : "Add Vehicle";

  $("submitButton").textContent =
    isEmergency
      ? "Plan Emergency Route →"
      : "Plan Vehicle Route →";

  $("vehicleType").value =
    isEmergency ? "Ambulance" : "Car";

  $("modalSource").value = $("source").value;
  $("modalDestination").value = $("destination").value;

  $("formError").textContent = "";
  $("registration").value = "";

  updateRegistrationField();

  $("modalBackdrop").hidden = false;
}


function closeModal() {
  $("modalBackdrop").hidden = true;
}


// Add Vehicle button
$("addVehicle").addEventListener("click", () => {
  openModal(false);
});


// Add Emergency button
$("addEmergency").addEventListener("click", () => {
  $("emergencyFormError").textContent = "";
  $("emergencyBackdrop").hidden = false;
});

// Close modal button
$("closeModal").addEventListener("click", closeModal);


// Close modal by clicking outside
$("modalBackdrop").addEventListener("click", event => {
  if (event.target === $("modalBackdrop")) {
    closeModal();
  }
});


// Close modals with Escape key
document.addEventListener("keydown", event => {
  if (event.key === "Escape") {
    closeModal();
    $("emergencyBackdrop").hidden = true;
    closeResponseModal();
  }
});

// Close emergency modal button
$("closeEmergencyModal").addEventListener("click", () => {
  $("emergencyBackdrop").hidden = true;
});

// Close emergency modal by clicking outside
$("emergencyBackdrop").addEventListener("click", event => {
  if (event.target === $("emergencyBackdrop")) {
    $("emergencyBackdrop").hidden = true;
  }
});

// Close response window
function closeResponseModal() {
  $("responseBackdrop").hidden = true;
}

$("closeResponseModal").addEventListener(
  "click",
  closeResponseModal
);

$("responseDone").addEventListener(
  "click",
  closeResponseModal
);

$("responseBackdrop").addEventListener("click", event => {
  if (event.target === $("responseBackdrop")) {
    closeResponseModal();
  }
});

// Show fields according to emergency type
$("emergencyType").addEventListener("change", () => {
  const type = $("emergencyType").value;

  $("medicalFields").hidden = type !== "MEDICAL";
  $("fireFields").hidden = type !== "FIRE";
  $("earthquakeFields").hidden = type !== "EARTHQUAKE";
});


// Vehicle type change
$("vehicleType").addEventListener(
  "change",
  updateRegistrationField
);


// Registration input formatting
$("registration").addEventListener("input", event => {
  event.target.value = event.target.value
    .toUpperCase()
    .replace(/[^A-Z0-9]/g, "");
});


// Vehicle form submission
$("vehicleForm").addEventListener("submit", event => {
  event.preventDefault();

  const vehicleType = $("vehicleType").value;
  const registration = $("registration").value.trim();

  const source = $("modalSource").value;
  const destination = $("modalDestination").value;

  const error = $("formError");
  error.textContent = "";

  // Registration validation
  if (
    vehicleType !== "Bicycle" &&
    !/^[A-Z]{2}[A-Z0-9]+$/.test(registration)
  ) {
    error.textContent =
      "Start with two letters, followed by letters or numbers only.";
    return;
  }

  // Source and destination validation
  if (source === destination) {
    error.textContent =
      "Choose different source and destination locations.";
    return;
  }

  // Update route planner
  $("source").value = source;
  $("destination").value = destination;
  $("plannerVehicle").value = vehicleType;

  // Calculate route
  showRoute(
    source,
    destination,
    vehicleType,
    vehicleType === "Bicycle" ? "Bicycle" : registration,
    true
  );

  closeModal();
});


/* =========================================================
   17. SIDEBAR NAVIGATION
   ========================================================= */

document.querySelectorAll("[data-scroll]").forEach(button => {
  button.addEventListener("click", () => {
    const target = $(button.dataset.scroll);

    if (!target) return;

    target.scrollIntoView({
      behavior: "smooth",
      block: "start"
    });
  });
});


/* =========================================================
   18. CLOCK
   ========================================================= */

function updateClock() {
  $("clock").textContent =
    new Date().toLocaleTimeString([], {
      hour: "2-digit",
      minute: "2-digit"
    });
}

updateClock();

setInterval(updateClock, 30000);


/* =========================================================
   19. INITIALIZATION COMPLETE
   ========================================================= */

console.log("Adaptive Traffic System loaded successfully.");
console.log("Locations:", locations.length);
console.log("Road segments:", roads.length);
console.log("Horizontal roads: 30");
console.log("Vertical roads: 28");
console.log("Diagonal roads: 12");
console.log("Routing algorithm: Congestion-aware Dijkstra");


/* =========================================================
   20. EMERGENCY FORM AND RESPONSE WINDOW
   ========================================================= */


/* =========================================================
   20. EMERGENCY FORM AND RESPONSE WINDOW
   Frontend simulation based on addemergency.cpp
   ========================================================= */

let emergencyRecords = [];

// Resource availability copied from addemergency.cpp
const resourceStations = [
  { id:"H1", name:"Doon Hospital", type:"Hospital", ambulances:9, beds:25 },
  { id:"H2", name:"Shri Mahant Indiresh Hospital", type:"Hospital", ambulances:9, beds:25 },
  { id:"H3", name:"Max Super Speciality Hospital", type:"Hospital", ambulances:9, beds:25 },
  { id:"H4", name:"Graphic Era Hospital", type:"Hospital", ambulances:9, beds:25 },
  { id:"H5", name:"Synergy Hospital", type:"Hospital", ambulances:9, beds:25 },
  { id:"H6", name:"Coronation Hospital", type:"Hospital", ambulances:6, beds:18 },
  { id:"H7", name:"Combined Medical Institute", type:"Hospital", ambulances:6, beds:18 },
  { id:"H8", name:"Prem Sukh Hospital", type:"Hospital", ambulances:6, beds:18 },
  { id:"H9", name:"Uttaranchal Hospital", type:"Hospital", ambulances:6, beds:18 },

  { id:"P1", name:"Dalanwala Police Station", type:"Police Station", police:3 },
  { id:"P2", name:"Nehru Colony Police Station", type:"Police Station", police:3 },
  { id:"P3", name:"Patel Nagar Police Station", type:"Police Station", police:3 },
  { id:"P4", name:"Rajpur Police Station", type:"Police Station", police:3 },
  { id:"P5", name:"Clement Town Police Station", type:"Police Station", police:3 },

  { id:"F1", name:"Dehradun Fire Station", type:"Fire Station", fire:2 },
  { id:"F2", name:"Doiwala Fire Station", type:"Fire Station", fire:2 },
  { id:"F3", name:"Selaqui Fire Station", type:"Fire Station", fire:2 },
  { id:"F4", name:"Mussoorie Fire Station", type:"Fire Station", fire:2 },

  { id:"R1", name:"Dehradun Central Emergency Rescue Hub",
    type:"Rescue Hub", rescueVans:20, rescueCapacity:500 },
  { id:"R2", name:"Saharanpur Chowk Emergency Rescue Hub",
    type:"Rescue Hub", rescueVans:13, rescueCapacity:300 }
];

// C++ vehicle speeds
speeds["Police Jeep"] = 45;
speeds["Rescue Van"] = 35;

// Same requirement calculations as addemergency.cpp
function emergencyRequirements(emergency) {
  const required = {
    ambulances: Math.ceil(emergency.injured / 3),
    fire: 0,
    police: 0,
    rescueVans: 0,
    beds: emergency.injured,
    rescueCapacity: 0
  };

  if (emergency.type === "FIRE") {
    required.fire = emergency.severity;
    required.police = 1;
    required.rescueVans = Math.ceil(emergency.trapped / 25);
    required.rescueCapacity = emergency.trapped;
  }

  if (emergency.type === "EARTHQUAKE") {
    const peopleToRescue = emergency.trapped + emergency.evacuation;

    required.rescueVans = Math.ceil(peopleToRescue / 25);
    required.rescueCapacity = peopleToRescue;
    required.police = 1;
  }

  return required;
}

// Find nearest stations and allocate available vehicles
function allocateVehicles(location, resourceKey, required, vehicleType) {
  let missing = required;
  const allocations = [];

  if (required <= 0) {
    return { allocations, missing: 0 };
  }

  const candidates = resourceStations
    .filter(station => (station[resourceKey] || 0) > 0)
    .map(station => {
      const route = calculateRoute(station.id, location, vehicleType);
      return route ? { station, route } : null;
    })
    .filter(Boolean)
    .sort((a, b) => a.route.minutes - b.route.minutes);

  candidates.forEach(({ station, route }) => {
    if (missing <= 0) return;

    const quantity = Math.min(station[resourceKey], missing);

    if (quantity > 0) {
      allocations.push({ station, quantity, route, vehicleType });
      missing -= quantity;
    }
  });

  return { allocations, missing };
}

// Find nearest hospitals and rescue hubs
function allocateCapacity(location, resourceKey, required, vehicleType) {
  let missing = required;
  const allocations = [];

  if (required <= 0) {
    return { allocations, missing: 0 };
  }

  const stationType = resourceKey === "beds" ? "Hospital" : "Rescue Hub";

  const candidates = resourceStations
    .filter(station =>
      station.type === stationType && (station[resourceKey] || 0) > 0
    )
    .map(station => {
      const route = calculateRoute(location, station.id, vehicleType);
      return route ? { station, route } : null;
    })
    .filter(Boolean)
    .sort((a, b) => a.route.minutes - b.route.minutes);

  candidates.forEach(({ station, route }) => {
    if (missing <= 0) return;

    const quantity = Math.min(station[resourceKey], missing);

    if (quantity > 0) {
      allocations.push({ station, quantity, route, vehicleType });
      missing -= quantity;
    }
  });

  return { allocations, missing };
}

function planEmergencyAllocation(emergency) {
  const required = emergencyRequirements(emergency);

  const result = {
    ambulances: allocateVehicles(
      emergency.location, "ambulances",
      required.ambulances, "Ambulance"
    ),

    fire: allocateVehicles(
      emergency.location, "fire",
      required.fire, "Fire Truck"
    ),

    police: allocateVehicles(
      emergency.location, "police",
      required.police, "Police Jeep"
    ),

    rescueVans: allocateVehicles(
      emergency.location, "rescueVans",
      required.rescueVans, "Rescue Van"
    ),

    hospitals: allocateCapacity(
      emergency.location, "beds",
      required.beds, "Ambulance"
    ),

    rescueHubs: allocateCapacity(
      emergency.location, "rescueCapacity",
      required.rescueCapacity, "Rescue Van"
    )
  };

  const fullyAllocated = Object.values(result)
    .every(group => group.missing === 0);

  return { result, fullyAllocated };
}

function assignedVehicleCount(result) {
  return ["ambulances", "fire", "police", "rescueVans"]
    .reduce((total, key) => {
      return total + result[key].allocations.reduce(
        (sum, item) => sum + item.quantity, 0
      );
    }, 0);
}

function allocationCard(title, group, quantityLabel = "Vehicles") {
  return group.allocations.map(item => `
    <div class="resource-result">
      <h4>${title} · ${item.station.name}</h4>
      <p><strong>${quantityLabel}:</strong> ${item.quantity}</p>
      <p><strong>Route:</strong> ${item.route.path.join(" → ")}</p>
      <p><strong>Distance:</strong> ${item.route.distance.toFixed(1)} km</p>
      <p><strong>Estimated travel time:</strong>
        ${Math.max(1, Math.round(item.route.minutes))} min
      </p>
    </div>
  `).join("");
}

function displayEmergencyAllocation(emergency, allocation) {
  const result = allocation.result;
  const totalVehicles = assignedVehicleCount(result);

  $("responseHeading").textContent = allocation.fullyAllocated
    ? "Resources Allocated"
    : "Partial Resource Availability";

  $("responseMessage").textContent =
    `${totalVehicles} vehicle(s) identified for the emergency at ` +
    `${names[emergency.location]}. This is a simulated plan; no real vehicles have been dispatched.`;

  let html = `
    <div class="resource-result">
      <h4>Emergency Summary</h4>
      <p><strong>Type:</strong> ${emergency.type}</p>
      <p><strong>Location:</strong> ${names[emergency.location]}</p>
      <p><strong>Injured people:</strong> ${emergency.injured}</p>
      <p><strong>Trapped people:</strong> ${emergency.trapped}</p>
      <p><strong>Additional evacuation:</strong> ${emergency.evacuation}</p>
      <p><strong>Vehicles assigned:</strong> ${totalVehicles}</p>
    </div>
  `;

  html += allocationCard("Ambulance", result.ambulances);
  html += allocationCard("Fire Truck", result.fire);
  html += allocationCard("Police Jeep", result.police);
  html += allocationCard("Rescue Van", result.rescueVans);
  html += allocationCard("Hospital", result.hospitals, "Beds allocated");
  html += allocationCard("Rescue Hub", result.rescueHubs, "People accommodated");

  const missing = [
    ["Ambulances", result.ambulances],
    ["Fire trucks", result.fire],
    ["Police jeeps", result.police],
    ["Rescue vans", result.rescueVans],
    ["Hospital beds", result.hospitals],
    ["Rescue capacity", result.rescueHubs]
  ].filter(([, group]) => group.missing > 0);

  if (missing.length) {
    html += `
      <div class="resource-result">
        <h4>Resources Unavailable</h4>
        ${missing.map(([name, group]) =>
          `<p>${name}: ${group.missing} still required</p>`
        ).join("")}
        <p>Emergency remains pending until all required resources are available.</p>
      </div>
    `;
  }

  $("assignedResources").innerHTML = html;

  // Choose the fastest assigned vehicle route for the main Route Analysis.
  const vehicleAssignments = [
    ...result.ambulances.allocations,
    ...result.fire.allocations,
    ...result.police.allocations,
    ...result.rescueVans.allocations
  ].sort((a, b) => a.route.minutes - b.route.minutes);

  
  if (vehicleAssignments.length) {
    showEmergencyRoutes(vehicleAssignments);
  } else {
    $("routeSubtitle").textContent =
      `Emergency · ${names[emergency.location]}`;

    drawNetwork([emergency.location]);
  }

}

// Submit emergency form
$("emergencyForm").addEventListener("submit", event => {
  event.preventDefault();

  const type = $("emergencyType").value;
  const location = $("emergencyLocation").value;
  const description = $("emergencyDescription").value.trim();
  const error = $("emergencyFormError");

  error.textContent = "";

  let injured = 0;
  let trapped = 0;
  let evacuation = 0;
  let severity = 0;

  if (!location || !description) {
    error.textContent = "Please fill in all required fields.";
    return;
  }

  if (type === "MEDICAL") {
    injured = Number($("medicalInjured").value);

    if (!Number.isInteger(injured) || injured < 1) {
      error.textContent = "Enter at least 1 injured person.";
      return;
    }
  } else if (type === "FIRE") {
    severity = Number($("fireSeverity").value);
    injured = Number($("fireInjured").value);
    trapped = Number($("fireTrapped").value);

    if (
      !Number.isInteger(injured) ||
      !Number.isInteger(trapped) ||
      injured < 0 || trapped < 0 ||
      injured + trapped < 1
    ) {
      error.textContent = "Enter valid injured and trapped people.";
      return;
    }
  } else if (type === "EARTHQUAKE") {
    trapped = Number($("earthquakeTrapped").value);
    injured = Number($("earthquakeInjured").value);
    evacuation = Number($("earthquakeEvacuation").value);

    if (
      ![trapped, injured, evacuation].every(
        value => Number.isInteger(value) && value >= 0
      ) ||
      trapped + injured + evacuation < 1
    ) {
      error.textContent = "Enter valid affected people.";
      return;
    }
  }

  const emergency = {
    id: emergencyRecords.length + 1,
    type,
    location,
    description,
    injured,
    trapped,
    evacuation,
    severity,
    status: "REPORTED"
  };

  const allocation = planEmergencyAllocation(emergency);

  // Match C++ behaviour: reserve resources only if everything is available.
  if (allocation.fullyAllocated) {
    const result = allocation.result;

    const resourceKeys = {
      ambulances: "ambulances",
      fire: "fire",
      police: "police",
      rescueVans: "rescueVans",
      hospitals: "beds",
      rescueHubs: "rescueCapacity"
    };

    Object.entries(resourceKeys).forEach(([groupKey, stationKey]) => {
      result[groupKey].allocations.forEach(item => {
        item.station[stationKey] -= item.quantity;
      });
    });

    emergency.status = "Resources Allocated";
  } else {
    emergency.status = "Pending";
  }

  emergencyRecords.push(emergency);

  displayEmergencyAllocation(emergency, allocation);

  // Open response popup and close reporting form.
  $("emergencyBackdrop").hidden = true;
  $("responseBackdrop").hidden = false;

  $("emergencyForm").reset();
  $("emergencyType").dispatchEvent(new Event("change"));
});
