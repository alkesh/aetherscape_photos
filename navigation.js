function nextPage(){
	document.location=unescape(nextPageUrl);
}
function prevPage(){
	document.location=unescape(prevPageUrl);
}
function parentPage(){
	document.location=unescape(parentPageUrl);
}


function initKeyboard() {
	document.onkeydown = IEGeckoKeyPress;
}


//IE&Gecko Code
function IEGeckoKeyPress(oEvent) {
	if (!oEvent) var oEvent = window.event;
	if (oEvent.keyCode) myKeyCode = oEvent.keyCode;
	else if (oEvent.which) myKeyCode = oEvent.which;
	if (oEvent.repeat || takenAction) {	return;	}
	if (myKeyCode >= 16 && myKeyCode <= 18) { return; }
	if (oEvent.shiftKey) { myKeyCode += 1000; }
	if (oEvent.ctrlKey)  { myKeyCode += 2000; }
	if (oEvent.altKey)   { myKeyCode += 4000; }
	//alert(oEvent.type + "=" + myKeyCode);
	myKeyPress(myKeyCode);
}

function myKeyPress(myKeyCode) {
	switch (myKeyCode) {
		case 39:					// RIGHT arrow
			takenAction = true;
			nextPage();
			break;
		case 107:					// NUM +
		case 37:					// LEFT arrow
			takenAction = true;
			prevPage();
			break;
		case 109:					// NUM -
			break;
		case 33: 					// Page UP
			break;
		case 36:					// HOME
			takenAction = true;
			parentPage();
			break;
		case 35:					// END
			break;
		case 83:					// S,s
		case 27:					// ESC
			break;
		case 73:					// I,i
			break;
		case 34:					// Page DOWN
		case 90:					// Z,z
			break;
		default:	 
			//alert(oEvent.type + "=" + myKeyCode);
			break;
		}
}
