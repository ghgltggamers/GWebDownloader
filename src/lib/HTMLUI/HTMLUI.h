#ifndef HTMLUI_H
#define HTMLUI_H

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <functional>
#include <unordered_map>
#include <string>

class HTMLUI {
public:
    HTMLUI(const std::string& title, int width, int height);
    ~HTMLUI();

    // Loads HTML content from a string
    void loadHTML(const std::string& html);

    // Loads HTML content from a file
    void loadFile(const std::string& filepath);

    // Registers a C++ function to be callable from JS
    void registerFunction(const std::string& functionName, std::function<void(const std::string&)> callback);

    // Runs the GTK main loop
    void run();

private:
    GtkWidget* window;
    WebKitWebView* webView;
    std::unordered_map<std::string, std::function<void(const std::string&)>> jsFunctions;

    // Initializes GTK and WebKit
    void initialize(const std::string& title, int width, int height);

    // JavaScript message handler
    static void jsCallback(WebKitUserContentManager* manager,
                           WebKitJavascriptResult* jsResult,
                           gpointer userData);

    // Helper to execute JavaScript within WebView
    void executeJS(const std::string& script);
};

HTMLUI::HTMLUI(const std::string& title, int width, int height) {
    initialize(title, width, height);
}

HTMLUI::~HTMLUI() {
    gtk_widget_destroy(window);
}

void HTMLUI::initialize(const std::string& title, int width, int height) {
    gtk_init(nullptr, nullptr);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), title.c_str());
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);

    WebKitUserContentManager* contentManager = webkit_user_content_manager_new();
    webView = WEBKIT_WEB_VIEW(webkit_web_view_new_with_user_content_manager(contentManager));
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(webView));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Connect JavaScript callback handler
    g_signal_connect(contentManager, "script-message-received::nativeCallback", G_CALLBACK(jsCallback), this);
    webkit_user_content_manager_register_script_message_handler(contentManager, "nativeCallback");

    gtk_widget_show_all(window);
}

void HTMLUI::loadHTML(const std::string& html) {
    webkit_web_view_load_html(webView, html.c_str(), nullptr);
}

void HTMLUI::loadFile(const std::string& filepath) {
    webkit_web_view_load_uri(webView, ("file://" + filepath).c_str());
}

void HTMLUI::registerFunction(const std::string& functionName, std::function<void(const std::string&)> callback) {
    jsFunctions[functionName] = callback;
}

void HTMLUI::run() {
    gtk_main();
}

void HTMLUI::jsCallback(WebKitUserContentManager* manager,
                        WebKitJavascriptResult* jsResult,
                        gpointer userData) {
    HTMLUI* ui = static_cast<HTMLUI*>(userData);
    JSCValue* value = webkit_javascript_result_get_js_value(jsResult);

    if (jsc_value_is_string(value)) {
        gchar* message = jsc_value_to_string(value);
        std::string functionCall(message);
        g_free(message);

        // Parse function name and argument from the message
        auto pos = functionCall.find(":");
        if (pos != std::string::npos) {
            std::string functionName = functionCall.substr(0, pos);
            std::string argument = functionCall.substr(pos + 1);

            // Execute the registered C++ callback
            if (ui->jsFunctions.find(functionName) != ui->jsFunctions.end()) {
                ui->jsFunctions[functionName](argument);
            }
        }
    }
                        }

                        void HTMLUI::executeJS(const std::string& script) {
                            webkit_web_view_run_javascript(webView, script.c_str(), nullptr, nullptr, nullptr);
                        }

                        #endif // HTMLUI_H