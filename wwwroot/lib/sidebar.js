"use strict";import{getTheme,setTheme}from"./theme-loader.js";const navToggle=$("#nav-toggle");const navClose=$("#nav-close");const settingsToggle=$("#settings-toggle");const sidebar=$("#sidebar");const container=$(".container");navToggle.on("click",(function(){sidebar.css("left","0px");container.addClass("active")}));navClose.on("click",(function(){sidebar.css("left","-250px");container.removeClass("active")}));settingsToggle.on("click",(function(){window.location.href="/settings.html"}));function onThemeButtonClick(){if(getTheme()=="light"){setTheme("dark")}else{setTheme("light")}}export function syncThemeButton(){const themeButtonDiv=$("#theme-button");themeButtonDiv.empty();const themeButton=document.createElement("theme-button");themeButton.setAttribute("value",getTheme());themeButton.setAttribute("size","2");themeButton.addEventListener("click",onThemeButtonClick);themeButtonDiv.append(themeButton)}syncThemeButton();
