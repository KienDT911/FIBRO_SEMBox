/*********
  SEMBox ESP32 - Web Content Header
  Contains all embedded HTML, CSS, and JavaScript
  
  This file is auto-included by SEMBox.ino
  Edit this file to customize the web dashboard
*********/

#ifndef WEB_CONTENT_H
#define WEB_CONTENT_H

#include <Arduino.h>

// ===========================================
// INDEX.HTML - Main Dashboard Page
// ===========================================

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>FIBRO SEMBox Control Panel</title>
    <link rel="stylesheet" href="style.css">
    <link rel="icon" href="data:,">
</head>
<body>
    <!-- Loading Screen -->
    <div class="loading-screen" id="loading-screen">
        <div class="loading-content">
            <div class="loading-spinner"></div>
            <div class="loading-text">Loading FIBRO SEMBox...</div>
        </div>
    </div>

    <div class="container" id="main-container" style="display: none;">
        <header class="header">
            <div class="logo">
                <div class="logo-icon">
                    <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <path d="M12 2L2 7l10 5 10-5-10-5zM2 17l10 5 10-5M2 12l10 5 10-5"/>
                    </svg>
                </div>
                <div class="logo-text">
                    <h1>FIBRO</h1>
                    <span class="subtitle">SEM Box Dashboard</span>
                </div>
            </div>
            <div class="status-indicator">
                <span class="status-dot online"></span>
                <span class="status-text">System Online</span>
            </div>
        </header>

        <main class="dashboard">
            <section class="card status-card">
                <div class="card-header">
                    <h2>System Status</h2>
                    <span class="badge active">Active</span>
                </div>
                <div class="status-grid">
                    <div class="status-item">
                        <span class="label">Uptime</span>
                        <span class="value" id="uptime">--:--:--</span>
                    </div>
                    <div class="status-item">
                        <span class="label">IP Address</span>
                        <span class="value" id="ip-address">192.168.4.1</span>
                    </div>
                    <div class="status-item">
                        <span class="label">Clients</span>
                        <span class="value" id="clients">0</span>
                    </div>
                    <div class="status-item">
                        <span class="label">RAM</span>
                        <span class="value" id="memory">--</span>
                    </div>
                    <div class="status-item">
                        <span class="label">Flash</span>
                        <span class="value" id="flash">--</span>
                    </div>
                </div>
            </section>

            <section class="card controls-card">
                <div class="card-header">
                    <h2>LED Control</h2>
                </div>
                <div class="controls-grid">
                    <div class="control-item" id="led-control">
                        <div class="control-info">
                            <div class="control-icon led-icon">
                                <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <path d="M9 18h6M10 22h4M12 2v1M4.93 4.93l.71.71M2 12h1M4.93 19.07l.71-.71M19.07 4.93l-.71.71M22 12h-1M19.07 19.07l-.71-.71"/>
                                    <path d="M9 14a5 5 0 1 1 6 0v2H9v-2z"/>
                                </svg>
                            </div>
                            <div class="control-details">
                                <span class="control-name">Built-in LED</span>
                                <span class="control-state" id="led-state">OFF</span>
                            </div>
                        </div>
                        <div class="control-actions">
                            <button class="btn btn-toggle" onclick="toggleLED()" id="led-btn">
                                <span>TOGGLE</span>
                            </button>
                        </div>
                        <div class="status-bar">
                            <div class="status-fill" id="led-bar"></div>
                        </div>
                    </div>
                </div>
            </section>

            <section class="card parameter-card">
                <div class="card-header">
                    <h2>Rotary Table Parameter</h2>
                </div>
                <div class="parameter-form">
                    <div class="param-group">
                        <label class="param-label" for="division">Division</label>
                        <input type="number" id="division" class="param-input" min="1" max="9999" value="360" placeholder="360">
                        <span class="param-hint">Number of divisions (1-9999)</span>
                    </div>
                    <div class="param-group">
                        <label class="param-label" for="ratio">Gear Ratio (1:X)</label>
                        <input type="number" id="ratio" class="param-input" min="1" max="9999" step="0.001" value="90" placeholder="90">
                        <span class="param-hint">Table to gear ratio</span>
                    </div>
                    <div class="param-actions">
                        <button class="btn btn-save" onclick="saveParameters()">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" width="16" height="16">
                                <path d="M19 21H5a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h11l5 5v11a2 2 0 0 1-2 2z"/>
                                <polyline points="17 21 17 13 7 13 7 21"/>
                                <polyline points="7 3 7 8 15 8"/>
                            </svg>
                            <span>SAVE</span>
                        </button>
                        <button class="btn btn-load" onclick="loadParameters()">
                            <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" width="16" height="16">
                                <path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/>
                                <polyline points="7 10 12 15 17 10"/>
                                <line x1="12" y1="15" x2="12" y2="3"/>
                            </svg>
                            <span>LOAD</span>
                        </button>
                    </div>
                </div>
            </section>

            <section class="card actions-card">
                <div class="card-header">
                    <h2>Quick Actions</h2>
                </div>
                <div class="actions-grid">
                    <button class="action-btn" onclick="allOn()">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <path d="M18.36 6.64a9 9 0 1 1-12.73 0M12 2v10"/>
                        </svg>
                        <span>All ON</span>
                    </button>
                    <button class="action-btn" onclick="allOff()">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <circle cx="12" cy="12" r="10"/>
                            <path d="M4.93 4.93l14.14 14.14"/>
                        </svg>
                        <span>All OFF</span>
                    </button>
                    <button class="action-btn" onclick="refreshStatus()">
                        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                            <path d="M23 4v6h-6M1 20v-6h6"/>
                            <path d="M3.51 9a9 9 0 0 1 14.85-3.36L23 10M1 14l4.64 4.36A9 9 0 0 0 20.49 15"/>
                        </svg>
                        <span>Refresh</span>
                    </button>
                </div>
            </section>
        </main>

        <footer class="footer">
            <p>&copy; 2024 FIBRO SEMBox Industrial Control System</p>
            <p class="version">Version 1.0.0</p>
        </footer>
    </div>

    <div class="toast" id="toast">
        <span class="toast-message" id="toast-message"></span>
    </div>

    <script src="script.js"></script>
</body>
</html>
)rawliteral";


// ===========================================
// STYLE.CSS - Dashboard Stylesheet
// ===========================================

const char style_css[] PROGMEM = R"rawliteral(
/* ===========================================
   SEMBox Industrial Dashboard CSS
   FIBRO Corporate Theme - Orange/White/Blue
   =========================================== */

/* CSS Variables - FIBRO Color Palette */
:root {
    /* Primary Colors */
    --bg-primary: #f5f5f5;
    --bg-secondary: #ffffff;
    --bg-tertiary: #e8e8e8;
    --bg-card: #ffffff;
    
    /* Accent Colors */
    --accent-primary: #FF6600;
    --accent-secondary: #0047BA;
    --accent-warning: #f0b429;
    --accent-danger: #dc3545;
    --accent-success: #28a745;
    
    /* Text Colors */
    --text-primary: #333333;
    --text-secondary: #555555;
    --text-muted: #888888;
    
    /* Border Colors */
    --border-default: #dddddd;
    --border-muted: #eeeeee;
    
    /* Shadows */
    --shadow-sm: 0 1px 3px rgba(0, 0, 0, 0.08);
    --shadow-md: 0 4px 12px rgba(0, 0, 0, 0.1);
    --shadow-lg: 0 8px 24px rgba(0, 0, 0, 0.12);
    --shadow-glow: 0 0 20px rgba(255, 102, 0, 0.2);
    
    /* Transitions */
    --transition-fast: 0.15s ease;
    --transition-normal: 0.25s ease;
    --transition-slow: 0.4s ease;
    
    /* Border Radius */
    --radius-sm: 0;
    --radius-md: 0;
    --radius-lg: 0;
}

/* Reset & Base Styles */
*,
*::before,
*::after {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

html {
    font-size: 16px;
    scroll-behavior: smooth;
}

body {
    font-family: 'Segoe UI', -apple-system, sans-serif;
    background: var(--bg-primary);
    color: var(--text-primary);
    min-height: 100vh;
    line-height: 1.6;
}

/* Background Pattern */
body::before {
    content: '';
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background: 
        linear-gradient(90deg, var(--border-muted) 1px, transparent 1px) 0 0 / 60px 60px,
        linear-gradient(var(--border-muted) 1px, transparent 1px) 0 0 / 60px 60px;
    opacity: 0.5;
    pointer-events: none;
    z-index: -1;
}

/* ===========================================
   Container
   =========================================== */
.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 20px;
    min-height: 100vh;
    display: flex;
    flex-direction: column;
}

/* ===========================================
   Header Styles
   =========================================== */
.header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 20px 24px;
    background: var(--bg-card);
    border: 1px solid var(--border-default);
    border-radius: var(--radius-lg);
    margin-bottom: 24px;
    box-shadow: var(--shadow-md);
    border-top: 4px solid var(--accent-primary);
}

.logo {
    display: flex;
    align-items: center;
    gap: 16px;
}

.logo-icon {
    width: 48px;
    height: 48px;
    background: var(--accent-primary);
    border-radius: var(--radius-md);
    display: flex;
    align-items: center;
    justify-content: center;
    box-shadow: var(--shadow-glow);
}

.logo-icon svg {
    width: 28px;
    height: 28px;
    color: #ffffff;
}

.logo-text h1 {
    font-size: 1.75rem;
    font-weight: 700;
    color: var(--accent-secondary);
    line-height: 1;
}

.logo-text .subtitle {
    font-size: 0.875rem;
    color: var(--text-secondary);
    text-transform: uppercase;
    letter-spacing: 1px;
}

/* Status Indicator */
.status-indicator {
    display: flex;
    align-items: center;
    gap: 10px;
    padding: 8px 16px;
    background: var(--bg-tertiary);
    border-radius: var(--radius-sm);
    border: 1px solid var(--border-default);
}

.status-dot {
    width: 10px;
    height: 10px;
    border-radius: 0;
    background: var(--text-muted);
    animation: pulse 2s infinite;
}

.status-dot.online {
    background: var(--accent-success);
    box-shadow: 0 0 8px var(--accent-success);
}

@keyframes pulse {
    0%, 100% {
        opacity: 1;
        transform: scale(1);
    }
    50% {
        opacity: 0.7;
        transform: scale(1.1);
    }
}

.status-text {
    font-size: 0.875rem;
    color: var(--text-secondary);
    font-weight: 500;
}

/* ===========================================
   Dashboard Grid
   =========================================== */
.dashboard {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
    gap: 24px;
    flex: 1;
}

/* ===========================================
   Card Styles
   =========================================== */
.card {
    background: var(--bg-card);
    border: 1px solid var(--border-default);
    border-radius: var(--radius-lg);
    padding: 24px;
    box-shadow: var(--shadow-md);
    transition: transform var(--transition-normal), box-shadow var(--transition-normal);
    animation: fadeIn 0.5s ease forwards;
}

.card:hover {
    transform: translateY(-2px);
    box-shadow: var(--shadow-lg);
}

.card:nth-child(1) { animation-delay: 0.1s; }
.card:nth-child(2) { animation-delay: 0.2s; }
.card:nth-child(3) { animation-delay: 0.3s; }

.card-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 20px;
    padding-bottom: 16px;
    border-bottom: 1px solid var(--border-default);
}

.card-header h2 {
    font-size: 1.125rem;
    font-weight: 600;
    color: var(--text-primary);
}

/* Badge */
.badge {
    padding: 4px 12px;
    border-radius: 0;
    font-size: 0.75rem;
    font-weight: 600;
    text-transform: uppercase;
}

.badge.active {
    background: rgba(255, 102, 0, 0.15);
    color: var(--accent-primary);
    border: 1px solid rgba(255, 102, 0, 0.3);
}

/* ===========================================
   Status Card
   =========================================== */
.status-grid {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 16px;
}

.status-item {
    background: var(--bg-tertiary);
    padding: 16px;
    border-radius: var(--radius-md);
    border: 1px solid var(--border-muted);
    transition: border-color var(--transition-fast);
}

.status-item:hover {
    border-color: var(--accent-primary);
}

.status-item .label {
    display: block;
    font-size: 0.75rem;
    color: var(--text-muted);
    text-transform: uppercase;
    margin-bottom: 4px;
}

.status-item .value {
    display: block;
    font-size: 1.25rem;
    font-weight: 600;
    color: var(--accent-primary);
    font-family: 'Consolas', monospace;
}

/* ===========================================
   Controls Card
   =========================================== */
.controls-grid {
    display: flex;
    flex-direction: column;
    gap: 16px;
}

.control-item {
    background: var(--bg-tertiary);
    border: 1px solid var(--border-default);
    border-radius: var(--radius-md);
    padding: 20px;
    transition: all var(--transition-normal);
    position: relative;
    overflow: hidden;
}

.control-item:hover {
    border-color: var(--accent-secondary);
}

.control-item.active {
    border-color: var(--accent-primary);
    box-shadow: 0 0 20px rgba(255, 102, 0, 0.1);
}

.control-info {
    display: flex;
    align-items: center;
    gap: 16px;
    margin-bottom: 16px;
}

.control-icon {
    width: 48px;
    height: 48px;
    background: var(--bg-secondary);
    border-radius: var(--radius-sm);
    display: flex;
    align-items: center;
    justify-content: center;
    transition: all var(--transition-normal);
}

.control-icon svg {
    width: 24px;
    height: 24px;
    color: var(--text-secondary);
    transition: color var(--transition-normal);
}

.control-item.active .control-icon {
    background: var(--accent-primary);
}

.control-item.active .control-icon svg {
    color: #ffffff;
}

.control-details {
    flex: 1;
}

.control-name {
    display: block;
    font-weight: 600;
    font-size: 1rem;
    color: var(--text-primary);
}

.control-state {
    display: inline-block;
    font-size: 0.75rem;
    font-weight: 600;
    text-transform: uppercase;
    padding: 2px 8px;
    border-radius: 0;
    margin-top: 4px;
    background: rgba(248, 81, 73, 0.15);
    color: var(--accent-danger);
}

.control-item.active .control-state {
    background: rgba(255, 102, 0, 0.15);
    color: var(--accent-primary);
}

.control-actions {
    display: flex;
    gap: 10px;
}

/* ===========================================
   Button Styles
   =========================================== */
.btn {
    flex: 1;
    padding: 12px 20px;
    border: none;
    border-radius: var(--radius-sm);
    font-size: 0.875rem;
    font-weight: 600;
    cursor: pointer;
    transition: all var(--transition-fast);
    display: flex;
    align-items: center;
    justify-content: center;
    text-transform: uppercase;
}

.btn-toggle {
    background: var(--accent-primary);
    color: white;
    box-shadow: 0 2px 8px rgba(255, 102, 0, 0.3);
    width: 100%;
}

.btn-toggle:hover {
    transform: translateY(-2px);
    box-shadow: 0 4px 16px rgba(0, 71, 186, 0.4);
    background: var(--accent-secondary);
}

/* Status Bar */
.status-bar {
    height: 4px;
    background: var(--bg-secondary);
    border-radius: 0;
    margin-top: 16px;
    overflow: hidden;
}

.status-fill {
    height: 100%;
    width: 0;
    background: var(--accent-primary);
    border-radius: 0;
    transition: width var(--transition-slow);
}

.control-item.active .status-fill {
    width: 100%;
}

/* ===========================================
   Actions Card
   =========================================== */
.actions-card {
    grid-column: span 2;
}

.actions-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
    gap: 16px;
}

.action-btn {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    gap: 12px;
    padding: 24px 20px;
    background: var(--bg-tertiary);
    border: 1px solid var(--border-default);
    border-radius: var(--radius-md);
    cursor: pointer;
    transition: all var(--transition-normal);
    color: var(--text-secondary);
}

.action-btn svg {
    width: 32px;
    height: 32px;
    transition: all var(--transition-normal);
}

.action-btn span {
    font-size: 0.875rem;
    font-weight: 600;
    text-transform: uppercase;
}

.action-btn:hover {
    background: var(--accent-primary);
    border-color: var(--accent-primary);
    color: #ffffff;
    transform: translateY(-4px);
    box-shadow: var(--shadow-glow);
}

/* ===========================================
   Footer Styles
   =========================================== */
.footer {
    text-align: center;
    padding: 24px;
    margin-top: 24px;
    border-top: 1px solid var(--border-default);
    color: var(--text-muted);
}

.footer p {
    font-size: 0.875rem;
}

.footer .version {
    font-size: 0.75rem;
    margin-top: 4px;
}

/* ===========================================
   Toast Notification
   =========================================== */
.toast {
    position: fixed;
    bottom: 24px;
    right: 24px;
    padding: 16px 24px;
    background: var(--bg-card);
    border: 1px solid var(--accent-primary);
    border-radius: var(--radius-md);
    box-shadow: var(--shadow-lg);
    transform: translateX(calc(100% + 24px));
    transition: transform var(--transition-normal);
    z-index: 1000;
}

.toast.show {
    transform: translateX(0);
}

.toast-message {
    color: var(--text-primary);
    font-weight: 500;
}

/* ===========================================
   Loading State
   =========================================== */
.loading {
    position: relative;
    pointer-events: none;
}

.loading::after {
    content: '';
    position: absolute;
    top: 50%;
    left: 50%;
    width: 20px;
    height: 20px;
    margin: -10px 0 0 -10px;
    border: 2px solid transparent;
    border-top-color: var(--accent-primary);
    border-radius: 0;
    animation: spin 0.8s linear infinite;
}

@keyframes spin {
    to {
        transform: rotate(360deg);
    }
}

/* ===========================================
   Animations
   =========================================== */
@keyframes fadeIn {
    from {
        opacity: 0;
        transform: translateY(10px);
    }
    to {
        opacity: 1;
        transform: translateY(0);
    }
}

/* ===========================================
   Responsive Design
   =========================================== */
@media (max-width: 768px) {
    .container {
        padding: 12px;
    }
    
    .header {
        flex-direction: column;
        gap: 16px;
        text-align: center;
    }
    
    .logo {
        flex-direction: column;
    }
    
    .dashboard {
        grid-template-columns: 1fr;
    }
    
    .actions-card {
        grid-column: span 1;
    }
    
    .status-grid {
        grid-template-columns: 1fr;
    }
    
    .control-actions {
        flex-direction: column;
    }
    
    .actions-grid {
        grid-template-columns: repeat(3, 1fr);
    }
}

@media (max-width: 480px) {
    .logo-text h1 {
        font-size: 1.5rem;
    }
    
    .card {
        padding: 16px;
    }
    
    .control-item {
        padding: 16px;
    }
    
    .actions-grid {
        grid-template-columns: 1fr;
    }
    
    .action-btn {
        flex-direction: row;
        padding: 16px;
    }
    
    .action-btn svg {
        width: 24px;
        height: 24px;
    }
}

/* ===========================================
   Parameter Card Styles
   =========================================== */
.parameter-form {
    display: flex;
    flex-direction: column;
    gap: 20px;
}

.param-group {
    display: flex;
    flex-direction: column;
    gap: 6px;
}

.param-label {
    font-size: 0.875rem;
    font-weight: 600;
    color: var(--text-primary);
    text-transform: uppercase;
}

.param-input {
    padding: 12px 16px;
    border: 2px solid var(--border-default);
    border-radius: 0;
    font-size: 1.25rem;
    font-weight: 600;
    font-family: 'Consolas', monospace;
    color: var(--accent-primary);
    background: var(--bg-tertiary);
    transition: all var(--transition-fast);
    width: 100%;
}

.param-input:focus {
    outline: none;
    border-color: var(--accent-primary);
    background: var(--bg-secondary);
}

.param-input::-webkit-inner-spin-button,
.param-input::-webkit-outer-spin-button {
    opacity: 1;
    height: 30px;
}

.param-hint {
    font-size: 0.75rem;
    color: var(--text-muted);
}

.param-actions {
    display: flex;
    gap: 12px;
    margin-top: 8px;
}

.btn-save,
.btn-load {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 8px;
    padding: 12px 20px;
    border: none;
    border-radius: 0;
    font-size: 0.875rem;
    font-weight: 600;
    cursor: pointer;
    transition: all var(--transition-fast);
    text-transform: uppercase;
}

.btn-save {
    background: var(--accent-primary);
    color: white;
}

.btn-save:hover {
    background: var(--accent-secondary);
    transform: translateY(-2px);
}

.btn-load {
    background: var(--bg-tertiary);
    color: var(--text-secondary);
    border: 1px solid var(--border-default);
}

.btn-load:hover {
    background: var(--accent-secondary);
    color: white;
    border-color: var(--accent-secondary);
    transform: translateY(-2px);
}

/* ===========================================
   Loading Screen
   =========================================== */
.loading-screen {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: var(--bg-primary);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: 9999;
    transition: opacity 0.3s ease, visibility 0.3s ease;
}

.loading-screen.hidden {
    opacity: 0;
    visibility: hidden;
}

.loading-content {
    text-align: center;
}

.loading-spinner {
    width: 60px;
    height: 60px;
    border: 4px solid var(--border-default);
    border-top: 4px solid var(--accent-primary);
    margin: 0 auto 20px auto;
    animation: spin 1s linear infinite;
}

.loading-text {
    font-size: 1.25rem;
    font-weight: 600;
    color: var(--accent-primary);
    text-transform: uppercase;
    letter-spacing: 2px;
}

@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}
)rawliteral";


// ===========================================
// SCRIPT.JS - Dashboard JavaScript
// ===========================================

const char script_js[] PROGMEM = R"rawliteral(
/**
 * SEMBox Industrial Dashboard Controller
 * JavaScript for ESP32 Web Interface
 */

// Configuration
const CONFIG = {
    refreshInterval: 5000,
    toastDuration: 3000,
    requestTimeout: 5000
};

// State Management
let state = {
    led: false,
    uptime: 0,
    clients: 0,
    freeHeap: 0,
    totalHeap: 0,
    flashSize: 0,
    sketchSize: 0,
    division: 360,
    ratio: 90
};

let uptimeInterval = null;

// DOM Elements
const elements = {
    loadingScreen: document.getElementById('loading-screen'),
    mainContainer: document.getElementById('main-container'),
    led: {
        control: document.getElementById('led-control'),
        state: document.getElementById('led-state'),
        bar: document.getElementById('led-bar')
    },
    uptime: document.getElementById('uptime'),
    clients: document.getElementById('clients'),
    memory: document.getElementById('memory'),
    flash: document.getElementById('flash'),
    division: document.getElementById('division'),
    ratio: document.getElementById('ratio'),
    paramStatus: document.getElementById('param-status'),
    toast: document.getElementById('toast'),
    toastMessage: document.getElementById('toast-message')
};

// ===========================================
// LED Control Functions
// ===========================================

function toggleLED() {
    const currentState = state.led;
    const action = currentState ? 'off' : 'on';
    const url = '/LED/' + action;
    elements.led.control.classList.add('loading');
    
    sendRequest(url).then(() => {
        state.led = !currentState;
        updateControlUI('led', !currentState);
        showToast('LED turned ' + action.toUpperCase(), 'success');
    }).catch(error => {
        showToast('Failed to toggle LED: ' + error, 'error');
    }).finally(() => {
        elements.led.control.classList.remove('loading');
    });
}

// ===========================================
// Quick Action Functions
// ===========================================

function allOn() {
    showToast('Turning LED ON...', 'info');
    sendRequest('/LED/on').then(() => {
        state.led = true;
        updateAllUI();
        showToast('LED turned ON', 'success');
    }).catch(error => {
        showToast('Error: ' + error, 'error');
    });
}

function allOff() {
    showToast('Turning LED OFF...', 'info');
    sendRequest('/LED/off').then(() => {
        state.led = false;
        updateAllUI();
        showToast('LED turned OFF', 'success');
    }).catch(error => {
        showToast('Error: ' + error, 'error');
    });
}

function refreshStatus() {
    showToast('Refreshing status...', 'info');
    sendRequest('/status').then(response => response.json()).then(data => {
        state.led = data.led === 'on';
        state.uptime = data.uptime || 0;
        state.clients = data.clients || 0;
        state.freeHeap = data.freeHeap || 0;
        state.totalHeap = data.totalHeap || 0;
        state.flashSize = data.flashSize || 0;
        state.sketchSize = data.sketchSize || 0;
        state.division = data.division || 360;
        state.ratio = data.ratio || 90;
        updateAllUI();
        showToast('Status refreshed', 'success');
    }).catch(error => {
        showToast('Status refresh completed', 'success');
    });
}

// ===========================================
// Parameter Functions
// ===========================================

function saveParameters() {
    const division = parseInt(elements.division.value) || 360;
    const ratio = parseFloat(elements.ratio.value) || 90;
    
    if (division < 1 || division > 9999) {
        showToast('Division must be 1-9999', 'error');
        return;
    }
    if (ratio < 1 || ratio > 9999) {
        showToast('Ratio must be 1-9999', 'error');
        return;
    }
    
    showToast('Saving parameters to NVS...', 'info');
    sendRequest('/params/save?division=' + division + '&ratio=' + ratio)
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                state.division = division;
                state.ratio = ratio;
                showToast('Parameters saved to flash!', 'success');
                if (elements.paramStatus) {
                    elements.paramStatus.textContent = 'Saved';
                    elements.paramStatus.classList.add('active');
                }
            } else {
                showToast('Failed to save: ' + data.error, 'error');
            }
        }).catch(error => {
            showToast('Error saving: ' + error, 'error');
        });
}

function loadParameters() {
    showToast('Loading parameters from NVS...', 'info');
    sendRequest('/params/load')
        .then(response => response.json())
        .then(data => {
            state.division = data.division || 360;
            state.ratio = data.ratio || 90;
            if (elements.division) elements.division.value = state.division;
            if (elements.ratio) elements.ratio.value = state.ratio;
            showToast('Parameters loaded: Division=' + state.division + ', Ratio=1:' + state.ratio, 'success');
        }).catch(error => {
            showToast('Error loading: ' + error, 'error');
        });
}

// ===========================================
// UI Update Functions
// ===========================================

function updateControlUI(controlId, isOn) {
    const control = elements[controlId];
    if (!control) return;
    
    if (isOn) {
        control.control.classList.add('active');
    } else {
        control.control.classList.remove('active');
    }
    control.state.textContent = isOn ? 'ON' : 'OFF';
}

function updateAllUI() {
    updateControlUI('led', state.led);
    
    if (elements.uptime) {
        elements.uptime.textContent = formatUptime(state.uptime);
    }
    if (elements.clients) {
        elements.clients.textContent = state.clients;
    }
    if (elements.memory) {
        const used = Math.round((state.totalHeap - state.freeHeap) / 1024);
        const total = Math.round(state.totalHeap / 1024);
        elements.memory.textContent = used + '/' + total + ' KB';
    }
    if (elements.flash) {
        const usedMB = (state.sketchSize / 1024 / 1024).toFixed(2);
        const totalMB = (state.flashSize / 1024 / 1024).toFixed(1);
        elements.flash.textContent = usedMB + '/' + totalMB + ' MB';
    }
    if (elements.division) {
        elements.division.value = state.division;
    }
    if (elements.ratio) {
        elements.ratio.value = state.ratio;
    }
}

// ===========================================
// Helper Functions
// ===========================================

function sendRequest(url) {
    return new Promise((resolve, reject) => {
        const controller = new AbortController();
        const timeoutId = setTimeout(() => controller.abort(), CONFIG.requestTimeout);
        
        fetch(url, { signal: controller.signal }).then(response => {
            clearTimeout(timeoutId);
            if (response.ok) {
                resolve(response);
            } else {
                reject('HTTP ' + response.status);
            }
        }).catch(error => {
            clearTimeout(timeoutId);
            if (error.name === 'AbortError') {
                reject('Request timeout');
            } else {
                reject(error.message);
            }
        });
    });
}

function formatUptime(seconds) {
    const hrs = Math.floor(seconds / 3600);
    const mins = Math.floor((seconds % 3600) / 60);
    const secs = seconds % 60;
    return hrs.toString().padStart(2, '0') + ':' + 
           mins.toString().padStart(2, '0') + ':' + 
           secs.toString().padStart(2, '0');
}

function showToast(message, type) {
    type = type || 'info';
    const toast = elements.toast;
    const toastMessage = elements.toastMessage;
    
    if (!toast || !toastMessage) return;
    
    toastMessage.textContent = message;
    const colors = {
        success: '#3fb950',
        error: '#f85149',
        info: '#0099ff'
    };
    toast.style.borderColor = colors[type] || colors.info;
    toast.classList.add('show');
    
    setTimeout(() => {
        toast.classList.remove('show');
    }, CONFIG.toastDuration);
}

function startUptimeCounter() {
    if (uptimeInterval) {
        clearInterval(uptimeInterval);
    }
    uptimeInterval = setInterval(() => {
        state.uptime++;
        if (elements.uptime) {
            elements.uptime.textContent = formatUptime(state.uptime);
        }
    }, 1000);
}

// ===========================================
// Initialization
// ===========================================

function hideLoadingScreen() {
    if (elements.loadingScreen) {
        elements.loadingScreen.classList.add('hidden');
    }
    if (elements.mainContainer) {
        elements.mainContainer.style.display = 'flex';
    }
}

function initializeApp() {
    sendRequest('/status').then(response => response.json()).then(data => {
        state.led = data.led === 'on';
        state.uptime = data.uptime || 0;
        state.clients = data.clients || 0;
        state.freeHeap = data.freeHeap || 0;
        state.totalHeap = data.totalHeap || 0;
        state.flashSize = data.flashSize || 0;
        state.sketchSize = data.sketchSize || 0;
        state.division = data.division || 360;
        state.ratio = data.ratio || 90;
        updateAllUI();
        hideLoadingScreen();
        startUptimeCounter();
        console.log('SEMBox Dashboard initialized');
    }).catch(error => {
        console.error('Failed to load initial data:', error);
        // Still show UI after error with defaults
        setTimeout(() => {
            hideLoadingScreen();
            startUptimeCounter();
        }, 2000);
    });
}

document.addEventListener('DOMContentLoaded', () => {
    initializeApp();
});
)rawliteral";

#endif // WEB_CONTENT_H
