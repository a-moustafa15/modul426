function getDailyData() {
    var dailydata = [
        '2019-11-23T05:50:00',
        '2019-11-23T06:50:00',
        '2019-11-23T09:50:00',
        '2019-11-23T10:10:00',
        '2019-11-23T12:50:00',
        '2019-11-23T15:10:00',
        '2019-11-23T18:20:00',
        '2019-11-23T20:50:00'
    ]

    dailydata.forEach(timestamp => {
        var stamp = new Date(timestamp);
        day = stamp.getDay();
        time = stamp.getTime();
    });

    
}
