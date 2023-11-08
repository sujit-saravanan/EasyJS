function card (name, img, content) {
	const frag = document.createDocumentFragment();
	// <article class="card">
	const _2188702122106 = document.createElement(`article`);
	_2188702122106.setAttribute(`class`, `card`);
		// <header>
		const _2188702122108 = document.createElement(`header`);
		_2188702122106.appendChild(_2188702122108);
			// <h2>
			const _2188702122109 = document.createElement(`h2`);
			_2188702122108.appendChild(_2188702122109);
				// $(name)
				_2188702122109.appendChild(document.createTextNode(`$(name)`));
		// <img src="$(img)">
		const _2188702122111 = document.createElement(`img`);
		_2188702122111.setAttribute(`src`, `$(img)`);
		_2188702122106.appendChild(_2188702122111);
			// <div class="content">
			const _2188702122112 = document.createElement(`div`);
			_2188702122112.setAttribute(`class`, `content`);
			_2188702122111.appendChild(_2188702122112);
				// <p>
				const _2188702122114 = document.createElement(`p`);
				_2188702122112.appendChild(_2188702122114);
					// this is some $(content)!!!
					_2188702122114.appendChild(document.createTextNode(`this is some $(content)!!!`));
	frag.appendChild(_2188702122106);
	return frag;
}

