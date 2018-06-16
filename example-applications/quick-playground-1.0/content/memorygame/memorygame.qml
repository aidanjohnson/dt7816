/*
 * Copyright (c) 2011 Nokia Corporation.
 */

import Qt 4.7
import "memorygame.js" as GameLogic

Image {
    id: game

    property bool gameStarted: false
    property int cards: 24
    property int columns: 8
    property int rows: 3

    // Because the card.qml won't see the GameLogic java script we use this function
    function handleClick(index) {
        GameLogic.selectCard(index)
    }

    function initialize() {
        if(gameStarted == false) {
            gameStarted = true
            GameLogic.initBoard(cards)
            gameStarted = true
        }
    }

    anchors.fill: parent
    source: "back_memorygame.png"
    fillMode: "Stretch"
}
