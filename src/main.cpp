/*
 * Copyright (c) GWebDownloader 2024
 * Written by [authorname]
 * Check the LICENSE file for Licensing info
 * Check out the README.md file for more information
 */
// Source
#ifndef MAIN
#define MAIN 101010111
#include "GWebDownloader.h"

int main(int argc, char* argv[]){
   // config checks - start
   std::cout<<"Reading config...\n";
   std::string CONFIG_THEME_VAR; // variables for defining the configs
   std::ifstream config_theme("config/theme"); // theme config
   if (config_theme.is_open()){
      std::getline (config_theme, CONFIG_THEME_VAR);
      if (CONFIG_THEME_VAR == "light" || CONFIG_THEME_VAR == "dark"){

      }
      else {
         std::cout<<"Warning: Unknown theme was defined in the 'config/theme' file make sure to use 'light/dark' themes only, Result without these themes may be ugly UI\n";
      }
   }
   else {
      std::cout<<"Fixing config for 'theme'...\n";
      std::system("mkdir config");
      std::ofstream config_theme_out("config/theme");
      config_theme_out<<"light";
      std::cout<<"Fixing config for 'theme' done\n";
   }

   // ui config
   std::string ui_config_dat = "<head>"
      "  <style>"
      "     *{"
      "        box-shadow: 3px 3px 5px rgba(0,0,0,0.1);"
      "        user-select: none;"
      "        transition: 1s;"
      "     }"
      "     center *{"
      "        margin-left: 10px;"
      "        box-shadow: 0px 0px 0px 0px black;"
      "     }"
      "     button{"
      "        background-color: dodgerblue;"
      "        border: 0px;"
      "        border-radius: 5px;"
      "        color: white;"
      "        transition: .5s;"
      "        height: 40px;"
      "        cursor: pointer;"
      "        width: auto;"
      "        padding-left: 10px;"
      "        padding-right: 10px;"
      "     }"
      "     button:hover{"
      "        opacity: .8;"
      "     }"
      "     button:focus{"
      "        opacity: .6;"
      "     }"
      "     input{"
      "        border: 0px;"
      "        border-bottom: 2px solid dodgerblue;"
      "        outline: none;"
      "        height: 40px;"
      "        width: 150px;"
      "        background: transparent;"
      "     }"
      "     #dark{"
      "        background: #101010;"
      "     }"
      "     #dark .card{"
      "        background-color: #151515;"
      "        color: white;"
      "        width: 70%;"
      "        border-radius: 10px;"
      "        padding: 20px;"
      "     }"
      "     #dark input{color: white;}"
      "     #light .card{"
      "        background-color: whitesmoke;"
      "        color: white;"
      "        width: 70%;"
      "        border-radius: 10px;"
      "        padding: 20px;"
      "     }"
      "     body{display: flex;align-items: center;justify-content: center;}"
      "  </style>"
      "</head>"
      "<body id='" + CONFIG_THEME_VAR + "'>"
      "  <div class='card'>"
      "     <center>"
      "        <input id='search-input' type='url' placeholder='Enter the website url...'>"
      "        <button id='search-btn'>Go</button>"
      "        <div class='card' id='webview-wrapper' style='height: 0px;overflow: hidden;'>"
      "           <iframe src='https://www.example.com/' frameborder='0' id='webview-client' style='width: 100%; height: 460px; display: none;'></iframe>"
      "           <br>"
      "           <button id='download-btn'>Download</button> <input placeholder='Path to save the downloaded files for the website' id='pathTD'>"
      "           "
      "           <b id='info'></b>"
      "        </div>"
      "     </center>"
      "  </div>"
      "  <div style='position: absolute;top: 10px;right: 10px;'>"
      "     <button onclick='setTheme(\"light\")'>Light Theme</button><br><br>"
      "     <button onclick='setTheme(\"dark\")'>Dark Theme</button>"
      "  </div>"
      "</body>"
      "<script>"
      "  const input = document.getElementById('search-input');"
      "  const search_button = document.getElementById('search-btn');"
      "  const webview_wrapper = document.getElementById('webview-wrapper');"
      "  const webview_client = document.getElementById('webview-client');"
      "  const download_button = document.getElementById('download-btn');"
      "  const pathTD = document.getElementById('pathTD');"
      "  const info = document.getElementById('info');"
      "     search_button.addEventListener('click', ()=>{"
      "        webview_wrapper.style.height = '0px';"
      "        setTimeout(()=>{"
      "           webview_client.style.display = 'block';"
      "           webview_wrapper.style.height = '500px';"
      "           webview_client.src = input.value;"
      "        }, 1000);"
      "     });"
      "     download_button.addEventListener('click', ()=>{"
      "        info.innerHTML = 'downloading...';"
      "        alert('Downloading the website! The GWebDownloader will close automatically when download is finished. LAunch from console for download status.');"
      "        window.webkit.messageHandlers.nativeCallback.postMessage('setPathTD:'+pathTD.value);"
      "        window.webkit.messageHandlers.nativeCallback.postMessage('download:'+input.value);"
      "     });"
      "  function setTheme(theme){"
      "     document.body.id = theme;"
      "     window.webkit.messageHandlers.nativeCallback.postMessage('setTheme:'+theme);"
      "  }"
      "</script>";
   std::ofstream ui_config_txt("config/ui");
   ui_config_txt<<ui_config_dat;
   // ui config end
   // config checks - end

   HTMLUI ui("GWebDownloader - OpenSource Linux", 900, 700);
   
   ui.loadHTML(
      ui_config_dat
   );


   std::string pathTD = "";
   ui.registerFunction("setPathTD", [&pathTD](std::string path){
      pathTD = path;
   });
   ui.registerFunction("download", [&pathTD](std::string message){
      // for (int i = 0; i <= 100000;i++){
      //    std::cout<<"Downloading "<<message<<" "<<i<<" times.\n";
      // }
      std::string wget_prepare_command = "bin/wget --mirror --convert-links --adjust-extension --page-requisites --no-parent -e robots=off -P "+pathTD+" "+message;
      // std::cout<<wget_prepare_command<<"\n";
      std::system(wget_prepare_command.c_str());
      exit (3);
   });
   ui.registerFunction("setTheme", [](std::string theme){
      std::ofstream setTheme("config/theme");
      setTheme<<theme;
   });

   ui.run();
   return 0;
}
#endif