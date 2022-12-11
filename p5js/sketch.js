//https://editor.p5js.org/Mithru/sketches/Hk1N1mMQg
//https://gorillasun.de/blog/introduction-to-perlin-noise-in-p5js-and-processing
//https://genekogan.com/code/p5js-perlin-noise/
//
const TIMES=12;
let serial; // variable for the serial object
let latestData; // variable to hold the data
let x;
let y;
let width=600;
let height=800;
let speed1 = 0.05;
let speed2 = 0.05;
let val = 100;
let s = 5;
let time = 0.01;


function setup() {
  createCanvas(width,height);
  background(255);
  //connect the p5js with arduino
  serial = new p5.SerialPort();
  serial.open("/dev/tty.usbmodem14101");

  serial.on('data', gotData);

}


function gotData() {
  let currentString = serial.readLine();
  trim(currentString);
  if (!currentString) return;
  // console.log(currentString);
  latestData = currentString;
}
//draw the heart
function heart(x, y, size) {
  beginShape();  
  vertex(x, y);     
  bezierVertex(x - size / 2, y - size / 2, x - size, y + size / 3, x, y + size); 
  bezierVertex(x + size, y + size / 3, x + size / 2, y - size / 2, x, y);  
  endShape(CLOSE);  
}

function draw() {
   background(0);
  if (latestData != undefined) {//appear the draw when the data from arduino is ported
   console.log (latestData);
    if(latestData<80&&latestData >=70){
      push();
       noStroke();
       colorMode(HSB);
      //draw the noise
      for (var p=0; p*s < height; p++) {
        for (var q=0; q*s < width; q++) {
            var fillCol = noise(q/val, p/val, time)*550;
            fill(fillCol, 100, 100, 1);
            rect(q*s, p*s, s, s);
        }
    }
    time += 0.03;//set the noise with motion
      pop();
   } else if(latestData>=80){
      for (let t = 0; t < TIMES; t++) {
       push();
frameRate(8);
     x=random(0,800);
     y=random(0,600);
     x +=speed1;
     y +=speed2;
       if (x > width ) {
         speed1 = -speed1;
       }
       if (y > height ) {
         speed2 = -speed2;
       }//let love shapes move
     stroke(random(255), random(250),255,random(255));
     noFill();
     strokeWeight(random([1,2,4,6,8]));
      
     heart(x, y, random(5,200));
      
    
   pop();
   }}else{background(0);}
                            }

}