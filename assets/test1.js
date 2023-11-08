function deletePopup(popup_id) {
    document.getElementById("dim-overlay").remove();
    document.getElementById(popup_id).remove();
    // target.remove();
}

function createPopup (id, button_function, button_text) {
	const frag = document.createDocumentFragment();
	// <div id="dim-overlay" class="fix-top-left fill-width fill-height opacity-80 bg-overlay">
	const _2192482238621 = document.createElement(`div`);
	_2192482238621.setAttribute(`id`, `dim-overlay`);
	_2192482238621.setAttribute(`class`, `fix-top-left fill-width fill-height opacity-80 bg-overlay`);
	// <div id="${id}-popup-container" class="fix-top-left fill-width fill-height flex row justify-center">
	const _2192482238624 = document.createElement(`div`);
	_2192482238624.setAttribute(`id`, `${id}-popup-container`);
	_2192482238624.setAttribute(`class`, `fix-top-left fill-width fill-height flex row justify-center`);
		// <div class="flex col justify-center basis-1/4 z-index-10">
		const _2192482238626 = document.createElement(`div`);
		_2192482238626.setAttribute(`class`, `flex col justify-center basis-1/4 z-index-10`);
		_2192482238624.appendChild(_2192482238626);
			// <div class="padding-16 border-radius-16 bg-surface flex col gap-32 z-index-10">
			const _2192482238628 = document.createElement(`div`);
			_2192482238628.setAttribute(`class`, `padding-16 border-radius-16 bg-surface flex col gap-32 z-index-10`);
			_2192482238626.appendChild(_2192482238628);
				// <div class="flex row justify-end">
				const _2192482238629 = document.createElement(`div`);
				_2192482238629.setAttribute(`class`, `flex row justify-end`);
				_2192482238628.appendChild(_2192482238629);
					// <div class="font-size-largestest unselectable clickable fg-text hover-fg-love transition-duration-125" onclick="deletePopup('${id}-popup-container')">
					const _2192482238631 = document.createElement(`div`);
					_2192482238631.setAttribute(`class`, `font-size-largestest unselectable clickable fg-text hover-fg-love transition-duration-125`);
					_2192482238631.setAttribute(`onclick`, `deletePopup('${id}-popup-container')`);
					_2192482238629.appendChild(_2192482238631);
						// X
						_2192482238631.appendChild(document.createTextNode(`X`));
				// <div class="flex col gap-32 justify-center fill-height">
				const _2192482238634 = document.createElement(`div`);
				_2192482238634.setAttribute(`class`, `flex col gap-32 justify-center fill-height`);
				_2192482238628.appendChild(_2192482238634);
					// <div id="${id}-popup-content" class="flex col align-center gap-16">
					const _2192482238636 = document.createElement(`div`);
					_2192482238636.setAttribute(`id`, `${id}-popup-content`);
					_2192482238636.setAttribute(`class`, `flex col align-center gap-16`);
					_2192482238634.appendChild(_2192482238636);
				// <div class="flex row justify-end">
				const _2192482238638 = document.createElement(`div`);
				_2192482238638.setAttribute(`class`, `flex row justify-end`);
				_2192482238628.appendChild(_2192482238638);
					// <div class="padding-16 bg-iris border-radius-8 basis-1/4 font-size-largest center-text unselectable clickable hover-bg-love transition-duration-125" onclick="${button_function}">
					const _2192482238640 = document.createElement(`div`);
					_2192482238640.setAttribute(`class`, `padding-16 bg-iris border-radius-8 basis-1/4 font-size-largest center-text unselectable clickable hover-bg-love transition-duration-125`);
					_2192482238640.setAttribute(`onclick`, `${button_function}`);
					_2192482238638.appendChild(_2192482238640);
						// ${button_text}
						_2192482238640.appendChild(document.createTextNode(`${button_text}`));
	frag.appendChild(_2192482238621);
	frag.appendChild(_2192482238624);
	return frag;
}

function createPopupInput(input_type, placeholder_text) {
	const frag = document.createDocumentFragment();
	// <input type="${input_type}" class="padding-16 bg-base border-radius-8 fg-text placeholder-fg-subtle font-size-largest no-border" placeholder="${placeholder_text}">
	const _2192482238854 = document.createElement(`input`);
	_2192482238854.setAttribute(`type`, `${input_type}`);
	_2192482238854.setAttribute(`class`, `padding-16 bg-base border-radius-8 fg-text placeholder-fg-subtle font-size-largest no-border`);
	_2192482238854.setAttribute(`placeholder`, `${placeholder_text}`);
	frag.appendChild(_2192482238854);
	return frag;
}

function createLogInPrompt() {
    const frag = createPopup("login", "logIn()", "Log In");
    const content = frag.getElementById("login-popup-content");
    content.appendChild(createPopupInput("text", "Username"));
    content.appendChild(createPopupInput("password", "Password"));
    return frag;
}
function logIn() {
    console.log("log_in");
}

function createSignUpPrompt() {
    const frag = createPopup("signup", "signUp()", "Sign Up");
    frag.prepend()
    const content = frag.getElementById("signup-popup-content");
    content.appendChild(createPopupInput("text", "Username"));
    content.appendChild(createPopupInput("password", "Password"));
    content.appendChild(createPopupInput("password", "Confirm Password"));
    return frag;
}
function signUp() {
    console.log("sign_up");
}

