function deletePopup(popup_id) {
    document.getElementById("dim-overlay").remove();
    document.getElementById(popup_id).remove();
    // target.remove();
}

DomElement createPopup (id, button_function, button_text) {
    <div id="dim-overlay" class="fix-top-left fill-width fill-height opacity-80 bg-overlay"></div>
    <div id="${id}-popup-container" class="fix-top-left fill-width fill-height flex row justify-center">
        <div class="flex col justify-center basis-1/4 z-index-10">
            <div class="padding-16 border-radius-16 bg-surface flex col gap-32 z-index-10">

                <div class="flex row justify-end">
                    <div class="font-size-largestest unselectable clickable fg-text hover-fg-love transition-duration-125"  onclick="deletePopup('${id}-popup-container')">
                        X
                    </div>
                </div>

                <div class="flex col gap-32 justify-center fill-height">
                    <div id="${id}-popup-content" class="flex col align-center gap-16">
                    </div>
                </div>

                <div class="flex row justify-end">
                    <div class="padding-16 bg-iris border-radius-8 basis-1/4 font-size-largest center-text unselectable clickable hover-bg-love transition-duration-125" onclick="${button_function}">
                        ${button_text}
                    </div>
                </div>

            </div>
        </div>
    </div>
}

DomElement createPopupInput(input_type, placeholder_text) {
    <input type="${input_type}" class="padding-16 bg-base border-radius-8 fg-text placeholder-fg-subtle font-size-largest no-border" placeholder="${placeholder_text}"></input>
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
