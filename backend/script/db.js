const mongoose = require('mongoose');

const dbURI = 'mongodb+srv://kazuki:89827156@trail-101.9qewedx.mongodb.net/?retryWrites=true&w=majority&appName=trail-101';

mongoose.connect(dbURI, {
    useNewUrlParser: true,
    useUnifiedTopology: true
});

const db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function() {
    console.log('Connected to MongoDB');
});

module.exports = db;

