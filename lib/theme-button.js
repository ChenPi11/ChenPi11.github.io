(() => {
  const func = (root, initTheme, changeTheme) => {
    const $ = (s) => {
      let dom = root.querySelectorAll(s);
      return dom.length == 1 ? dom[0] : dom;
    };
    let mainButton = $(".main-button");
    let daytimeBackground = $(".daytime-background");
    let cloud = $(".cloud");
    let cloudList = $(".cloud-son");
    let cloudLight = $(".cloud-light");
    let components = $(".components");
    let moon = $(".moon");
    let stars = $(".stars");
    let star = $(".star");
    let isMoved = false;
    let isClicked = false;
    window.matchMedia("(prefers-color-scheme: dark)").addEventListener("change", () => {
      toggleThemeBasedOnSystem();
    });
    const toggleThemeBasedOnSystem = () => {
      if (window.matchMedia("(prefers-color-scheme: dark)").matches) {
        if (!isMoved) {
          components.onclick();
        }
      } else {
        if (isMoved) {
          components.onclick();
        }
      }
    };
    components.onclick = () => {
      if (isMoved) {
        mainButton.style.transform = "translateX(0)";
        mainButton.style.backgroundColor = "rgba(255, 195, 35,1)";

        mainButton.style.boxShadow =
          "3em 3em 5em rgba(0, 0, 0, 0.5), inset  -3em -5em 3em -3em rgba(0, 0, 0, 0.5), inset  4em 5em 2em -2em rgba(255, 230, 80,1)";

        daytimeBackground[0].style.transform = "translateX(0)";
        daytimeBackground[1].style.transform = "translateX(0)";
        daytimeBackground[2].style.transform = "translateX(0)";
        cloud.style.transform = "translateY(10em)";
        cloudLight.style.transform = "translateY(10em)";
        components.style.backgroundColor = "rgba(70, 133, 192,1)";

        moon[0].style.opacity = "0";
        moon[1].style.opacity = "0";
        moon[2].style.opacity = "0";

        stars.style.transform = "translateY(-125em)";
        stars.style.opacity = "0";

        changeTheme("light");
      } else {
        mainButton.style.transform = "translateX(110em)";
        mainButton.style.backgroundColor = "rgba(195, 200,210,1)";

        mainButton.style.boxShadow =
          "3em 3em 5em rgba(0, 0, 0, 0.5), inset  -3em -5em 3em -3em rgba(0, 0, 0, 0.5), inset  4em 5em 2em -2em rgba(255, 255, 210,1)";

        daytimeBackground[0].style.transform = "translateX(110em)";
        daytimeBackground[1].style.transform = "translateX(80em)";
        daytimeBackground[2].style.transform = "translateX(50em)";
        cloud.style.transform = "translateY(80em)";
        cloudLight.style.transform = "translateY(80em)";
        components.style.backgroundColor = "rgba(25,30,50,1)";

        moon[0].style.opacity = "1";
        moon[1].style.opacity = "1";
        moon[2].style.opacity = "1";

        stars.style.transform = "translateY(-62.5em)";
        stars.style.opacity = "1";

        changeTheme("dark");
      }

      isClicked = true;

      setTimeout(function () {
        isClicked = false;
      }, 500);
      isMoved = !isMoved;
    };

    mainButton.addEventListener("mousemove", function () {
      if (isClicked) return;

      if (isMoved) {
        mainButton.style.transform = "translateX(100em)";
        daytimeBackground[0].style.transform = "translateX(100em)";
        daytimeBackground[1].style.transform = "translateX(73em)";
        daytimeBackground[2].style.transform = "translateX(46em)";

        star[0].style.top = "10em";
        star[0].style.left = "36em";
        star[1].style.top = "40em";
        star[1].style.left = "87em";
        star[2].style.top = "26em";
        star[2].style.left = "16em";
        star[3].style.top = "38em";
        star[3].style.left = "63em";
        star[4].style.top = "20.5em";
        star[4].style.left = "72em";
        star[5].style.top = "51.5em";
        star[5].style.left = "35em";
      } else {
        mainButton.style.transform = "translateX(10em)";
        daytimeBackground[0].style.transform = "translateX(10em)";
        daytimeBackground[1].style.transform = "translateX(7em)";
        daytimeBackground[2].style.transform = "translateX(4em)";

        cloudList[0].style.right = "-24em";
        cloudList[0].style.bottom = "10em";
        cloudList[1].style.right = "-12em";
        cloudList[1].style.bottom = "-27em";
        cloudList[2].style.right = "17em";
        cloudList[2].style.bottom = "-43em";
        cloudList[3].style.right = "46em";
        cloudList[3].style.bottom = "-39em";
        cloudList[4].style.right = "70em";
        cloudList[4].style.bottom = "-65em";
        cloudList[5].style.right = "109em";
        cloudList[5].style.bottom = "-54em";
        cloudList[6].style.right = "-23em";
        cloudList[6].style.bottom = "10em";
        cloudList[7].style.right = "-11em";
        cloudList[7].style.bottom = "-26em";
        cloudList[8].style.right = "18em";
        cloudList[8].style.bottom = "-42em";
        cloudList[9].style.right = "47em";
        cloudList[9].style.bottom = "-38em";
        cloudList[10].style.right = "74em";
        cloudList[10].style.bottom = "-64em";
        cloudList[11].style.right = "110em";
        cloudList[11].style.bottom = "-55em";
      }
    });

    mainButton.addEventListener("mouseout", function () {
      if (isClicked) {
        return;
      }
      if (isMoved) {
        mainButton.style.transform = "translateX(110em)";
        daytimeBackground[0].style.transform = "translateX(110em)";
        daytimeBackground[1].style.transform = "translateX(80em)";
        daytimeBackground[2].style.transform = "translateX(50em)";

        star[0].style.top = "11em";
        star[0].style.left = "39em";
        star[1].style.top = "39em";
        star[1].style.left = "91em";
        star[2].style.top = "26em";
        star[2].style.left = "19em";
        star[3].style.top = "37em";
        star[3].style.left = "66em";
        star[4].style.top = "21em";
        star[4].style.left = "75em";
        star[5].style.top = "51em";
        star[5].style.left = "38em";
      } else {
        mainButton.style.transform = "translateX(0em)";
        daytimeBackground[0].style.transform = "translateX(0em)";
        daytimeBackground[1].style.transform = "translateX(0em)";
        daytimeBackground[2].style.transform = "translateX(0em)";

        cloudList[0].style.right = "-20em";
        cloudList[0].style.bottom = "10em";
        cloudList[1].style.right = "-10em";
        cloudList[1].style.bottom = "-25em";
        cloudList[2].style.right = "20em";
        cloudList[2].style.bottom = "-40em";
        cloudList[3].style.right = "50em";
        cloudList[3].style.bottom = "-35em";
        cloudList[4].style.right = "75em";
        cloudList[4].style.bottom = "-60em";
        cloudList[5].style.right = "110em";
        cloudList[5].style.bottom = "-50em";
        cloudList[6].style.right = "-20em";
        cloudList[6].style.bottom = "10em";
        cloudList[7].style.right = "-10em";
        cloudList[7].style.bottom = "-25em";
        cloudList[8].style.right = "20em";
        cloudList[8].style.bottom = "-40em";
        cloudList[9].style.right = "50em";
        cloudList[9].style.bottom = "-35em";
        cloudList[10].style.right = "75em";
        cloudList[10].style.bottom = "-60em";
        cloudList[11].style.right = "110em";
        cloudList[11].style.bottom = "-50em";
      }
    });

    const getRandomDirection = () => {
      const directions = ["2em", "-2em"];
      return directions[Math.floor(Math.random() * directions.length)];
    };

    const moveElementRandomly = (element) => {
      const randomDirectionX = getRandomDirection();
      const randomDirectionY = getRandomDirection();
      element.style.transform = `translate(${randomDirectionX}, ${randomDirectionY})`;
    };

    const cloudSons = root.querySelectorAll(".cloud-son");
    setInterval(() => {
      cloudSons.forEach(moveElementRandomly);
    }, 1000);

    if (initTheme === "dark") {
      components.onclick();
    }
  };

  class ThemeButton extends HTMLElement {
    constructor() {
      super();
    }
    connectedCallback() {
      const initTheme = this.getAttribute("value") || "light";
      const size = +this.getAttribute("size") || 3;
      const shadow = this.attachShadow({ mode: "closed" });
      const container = document.createElement("div");
      container.setAttribute("class", "theme-button-container");
      container.setAttribute("style", `font-size: ${(size / 3).toFixed(2)}px`);
      container.innerHTML =
        '<div class="components"><div class="main-button"><div class="moon"></div><div class="moon"></div><div class="moon"></div></div><div class="daytime-background"></div><div class="daytime-background"></div><div class="daytime-background"></div><div class="cloud"><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div></div><div class="cloud-light"><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div><div class="cloud-son"></div></div><div class="stars"><div class="star big"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div><div class="star big"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div><div class="star medium"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div><div class="star medium"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div><div class="star small"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div><div class="star small"><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div><div class="star-son"></div></div></div></div>';
      const style = document.createElement("link");
      style.setAttribute("rel", "stylesheet");
      style.setAttribute("href", "/lib/theme-button.css");
      const changeTheme = (detail) => {
        this.dispatchEvent(new CustomEvent("change", { detail }));
      };
      func(container, initTheme, changeTheme);
      shadow.appendChild(style);
      shadow.appendChild(container);
    }
  }

  customElements.define("theme-button", ThemeButton);
})();
