/*
 * Copyright (c) 2011 Nokia Corporation.
 */

var board = new Array(0)
var cardSource = "card.qml";
var component;  // will hold the card.qml which will be used to instantiate cards

var card1   // will hold the first selected card
var card2   // will hold the second selected card

// Function used to sort the array to random order
function randOrd() {
    return (Math.round(Math.random())-0.5);
}


function createCards() {
    if(component.status == Component.Error) {
        console.log("Error creating card component");
        console.log(component.errorString())
        return false;
    }

    for(var i=0; i<cards; i++) {
        var dynamicObject = component.createObject(game);
        if(dynamicObject == null) {
            print("Error creating card");
            return false;
        }
        dynamicObject.number = Math.floor(i / 2 + 1)
        board[i] = dynamicObject
    }

    board.sort(randOrd);
    for(var i=0; i<cards; i++) {
        board[i].index = i
        board[i].parent = game
        board[i].z = 1
        board[i].born()
    }
    return true;
}


// Creates new card objects and reparents them to the grid
// The cards are shuffle
function initBoard(cards) {
    for(var i=0; i<board.length; i++) {
        if(board[i] != null) {
            board[i].destroy();
        }
    }

    board = new Array(cards)

    if(component == null) {
        component = Qt.createComponent(cardSource);
        //component = createComponent(cardSource);

        if(component.status == Component.Loading) {
            component.statusChanged.connect(createCards)
        }
        else {
            createCards()
        }
    }
    else {
        createCards()
    }
}


function gameEndCheck() {
    var allVanished = true;

    for(var i=0; i<board.length;i++) {
        if(board[i].vanished == false) {
            allVanished = false;
            break;
        }
    }

    if(allVanished == true) {
        gameStarted = false
        for(var i=0; i<board.length; i++) {
            board[i].die();
        }
    }
}


function selectCard(index) {
    var card = board[index]

    if(card1 == null) {
        card1 = card;
        card.turned = true
    }
    else if(card2 == null) {
        if(card == card1) {
            // don't allow user select same card twice
            return
        }

        card2 = card;
        card.turned = true
    }
    else {
        card1.turned = false
        card2.turned = false
        card1 = null;
        card2 = null;
        return
    }

    if((card1 != null) && (card2 != null)) {
        if(card1.number == card2.number) {
            card1.vanish()
            card2.vanish()
            card1 = null;
            card2 = null;
            gameEndCheck()
        }
    }
}
