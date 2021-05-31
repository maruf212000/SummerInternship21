//Object 
/*const circle = {
    raduis : 1,
    location : {
        x: 1,
        y: 1
    },
    draw: function(){
        console.log("Draw");
    }
};

circle.draw();*/

//Factory Function
function createCircle(raduis){
    return{
        raduis,
        draw:function() {
            console.log('Draw');
        }
    };
}

const circle = createCircle(1);

//Constructor Function
function Circle(raduis){
    this.raduis = raduis;
    this.draw = function() {
        console.log("Draw");
    }
}

const another = new Circle;