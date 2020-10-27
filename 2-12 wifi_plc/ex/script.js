function realtime() {
    var rtClock = new Date();
    var second = rtClock.getSeconds();
    document.getElementById('clock').innerHTML = "<button>"+second+"</button>";
    //var t = setTimeout(realtime, 1000);
}