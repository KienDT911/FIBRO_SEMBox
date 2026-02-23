/**
 * SEMBox Industrial Dashboard Controller
 * JavaScript for ESP32 Web Interface
 */

// ===========================================
// Configuration
// ===========================================
const CONFIG = {
    refreshInterval: 5000,      // Status refresh interval (ms)
    toastDuration: 3000,        // Toast message duration (ms)
    requestTimeout: 5000,       // HTTP request timeout (ms)
    animationDuration: 300      // Animation duration (ms)
};

// ===========================================
// State Management
// ===========================================
let state = {
    gpio26: false,
    gpio27: false,
    led: false,
    uptime: 0,
    clients: 0,
    memory: '--'
};

let uptimeInterval = null;

// ===========================================
// DOM Elements
// ===========================================
const elements = {
    gpio26: {
        control: document.getElementById('gpio26-control'),
        state: document.getElementById('gpio26-state'),
        bar: document.getElementById('gpio26-bar')
    },
    gpio27: {
        control: document.getElementById('gpio27-control'),
        state: document.getElementById('gpio27-state'),
        bar: document.getElementById('gpio27-bar')
    },
    led: {
        control: document.getElementById('led-control'),
        state: document.getElementById('led-state'),
        bar: document.getElementById('led-bar')
    },
    uptime: document.getElementById('uptime'),
    clients: document.getElementById('clients'),
    memory: document.getElementById('memory'),
    toast: document.getElementById('toast'),
    toastMessage: document.getElementById('toast-message')
};

// ===========================================
// GPIO Control Functions
// ===========================================

/**
 * Toggle GPIO pin state
 * @param {number} pin - GPIO pin number (26 or 27)
 * @param {string} action - 'on' or 'off'
 */
function toggleGPIO(pin, action) {
    const url = `/${pin}/${action}`;
    const isOn = action === 'on';
    
    // Show loading state
    const controlElement = elements[`gpio${pin}`].control;
    controlElement.classList.add('loading');
    
    sendRequest(url)
        .then(() => {
            state[`gpio${pin}`] = isOn;
            updateControlUI(`gpio${pin}`, isOn);
            showToast(`GPIO ${pin} turned ${action.toUpperCase()}`, 'success');
        })
        .catch(error => {
            showToast(`Failed to toggle GPIO ${pin}: ${error}`, 'error');
        })
        .finally(() => {
            controlElement.classList.remove('loading');
        });
}

/**
 * Toggle Built-in LED state
 * @param {string} action - 'on' or 'off'
 */
function toggleLED(action) {
    const url = `/LED/${action}`;
    const isOn = action === 'on';
    
    // Show loading state
    elements.led.control.classList.add('loading');
    
    sendRequest(url)
        .then(() => {
            state.led = isOn;
            updateControlUI('led', isOn);
            showToast(`LED turned ${action.toUpperCase()}`, 'success');
        })
        .catch(error => {
            showToast(`Failed to toggle LED: ${error}`, 'error');
        })
        .finally(() => {
            elements.led.control.classList.remove('loading');
        });
}

// ===========================================
// Quick Action Functions
// ===========================================

/**
 * Turn all outputs ON
 */
function allOn() {
    showToast('Turning all outputs ON...', 'info');
    
    Promise.all([
        sendRequest('/26/on'),
        sendRequest('/27/on'),
        sendRequest('/LED/on')
    ])
    .then(() => {
        state.gpio26 = true;
        state.gpio27 = true;
        state.led = true;
        updateAllUI();
        showToast('All outputs turned ON', 'success');
    })
    .catch(error => {
        showToast(`Error: ${error}`, 'error');
    });
}

/**
 * Turn all outputs OFF
 */
function allOff() {
    showToast('Turning all outputs OFF...', 'info');
    
    Promise.all([
        sendRequest('/26/off'),
        sendRequest('/27/off'),
        sendRequest('/LED/off')
    ])
    .then(() => {
        state.gpio26 = false;
        state.gpio27 = false;
        state.led = false;
        updateAllUI();
        showToast('All outputs turned OFF', 'success');
    })
    .catch(error => {
        showToast(`Error: ${error}`, 'error');
    });
}

/**
 * Refresh status from server
 */
function refreshStatus() {
    showToast('Refreshing status...', 'info');
    
    sendRequest('/status')
        .then(response => response.json())
        .then(data => {
            state.gpio26 = data.gpio26 === 'on';
            state.gpio27 = data.gpio27 === 'on';
            state.led = data.led === 'on';
            state.uptime = data.uptime || 0;
            state.clients = data.clients || 0;
            state.memory = data.memory || '--';
            updateAllUI();
            showToast('Status refreshed', 'success');
        })
        .catch(error => {
            // Fallback: just confirm connection
            showToast('Status refresh completed', 'success');
        });
}

// ===========================================
// UI Update Functions
// ===========================================

/**
 * Update control UI based on state
 * @param {string} controlId - 'gpio26', 'gpio27', or 'led'
 * @param {boolean} isOn - Current state
 */
function updateControlUI(controlId, isOn) {
    const control = elements[controlId];
    if (!control) return;
    
    // Update control container class
    if (isOn) {
        control.control.classList.add('active');
    } else {
        control.control.classList.remove('active');
    }
    
    // Update state text
    control.state.textContent = isOn ? 'ON' : 'OFF';
}

/**
 * Update all UI elements
 */
function updateAllUI() {
    updateControlUI('gpio26', state.gpio26);
    updateControlUI('gpio27', state.gpio27);
    updateControlUI('led', state.led);
    
    // Update status display
    if (elements.uptime) {
        elements.uptime.textContent = formatUptime(state.uptime);
    }
    if (elements.clients) {
        elements.clients.textContent = state.clients;
    }
    if (elements.memory) {
        elements.memory.textContent = state.memory;
    }
}

// ===========================================
// Helper Functions
// ===========================================

/**
 * Send HTTP request with timeout
 * @param {string} url - Request URL
 * @returns {Promise} Response promise
 */
function sendRequest(url) {
    return new Promise((resolve, reject) => {
        const controller = new AbortController();
        const timeoutId = setTimeout(() => controller.abort(), CONFIG.requestTimeout);
        
        fetch(url, { signal: controller.signal })
            .then(response => {
                clearTimeout(timeoutId);
                if (response.ok) {
                    resolve(response);
                } else {
                    reject(`HTTP ${response.status}`);
                }
            })
            .catch(error => {
                clearTimeout(timeoutId);
                if (error.name === 'AbortError') {
                    reject('Request timeout');
                } else {
                    reject(error.message);
                }
            });
    });
}

/**
 * Format uptime in HH:MM:SS
 * @param {number} seconds - Uptime in seconds
 * @returns {string} Formatted time string
 */
function formatUptime(seconds) {
    const hrs = Math.floor(seconds / 3600);
    const mins = Math.floor((seconds % 3600) / 60);
    const secs = seconds % 60;
    return `${hrs.toString().padStart(2, '0')}:${mins.toString().padStart(2, '0')}:${secs.toString().padStart(2, '0')}`;
}

/**
 * Show toast notification
 * @param {string} message - Message to display
 * @param {string} type - 'success', 'error', or 'info'
 */
function showToast(message, type = 'info') {
    const toast = elements.toast;
    const toastMessage = elements.toastMessage;
    
    if (!toast || !toastMessage) return;
    
    // Set message and style
    toastMessage.textContent = message;
    
    // Set border color based on type
    const colors = {
        success: '#3fb950',
        error: '#f85149',
        info: '#0099ff'
    };
    toast.style.borderColor = colors[type] || colors.info;
    
    // Show toast
    toast.classList.add('show');
    
    // Hide after duration
    setTimeout(() => {
        toast.classList.remove('show');
    }, CONFIG.toastDuration);
}

/**
 * Start uptime counter
 */
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
// Keyboard Shortcuts
// ===========================================
document.addEventListener('keydown', (event) => {
    // Only handle if not in an input field
    if (event.target.tagName === 'INPUT' || event.target.tagName === 'TEXTAREA') {
        return;
    }
    
    switch (event.key.toLowerCase()) {
        case '1':
            toggleGPIO(26, state.gpio26 ? 'off' : 'on');
            break;
        case '2':
            toggleGPIO(27, state.gpio27 ? 'off' : 'on');
            break;
        case '3':
            toggleLED(state.led ? 'off' : 'on');
            break;
        case 'a':
            if (event.shiftKey) {
                allOn();
            }
            break;
        case 'o':
            if (event.shiftKey) {
                allOff();
            }
            break;
        case 'r':
            refreshStatus();
            break;
    }
});

// ===========================================
// Initialization
// ===========================================
document.addEventListener('DOMContentLoaded', () => {
    console.log('SEMBox Dashboard initialized');
    
    // Initialize UI
    updateAllUI();
    
    // Start uptime counter
    startUptimeCounter();
    
    // Initial status fetch
    setTimeout(() => {
        refreshStatus();
    }, 1000);
    
    // Add visual feedback for button clicks
    document.querySelectorAll('.btn, .action-btn').forEach(btn => {
        btn.addEventListener('click', function(e) {
            // Create ripple effect
            const ripple = document.createElement('span');
            ripple.style.cssText = `
                position: absolute;
                border-radius: 50%;
                background: rgba(255,255,255,0.3);
                transform: scale(0);
                animation: ripple 0.6s linear;
                pointer-events: none;
            `;
            
            const rect = this.getBoundingClientRect();
            const size = Math.max(rect.width, rect.height);
            ripple.style.width = ripple.style.height = size + 'px';
            ripple.style.left = (e.clientX - rect.left - size / 2) + 'px';
            ripple.style.top = (e.clientY - rect.top - size / 2) + 'px';
            
            this.style.position = 'relative';
            this.style.overflow = 'hidden';
            this.appendChild(ripple);
            
            setTimeout(() => ripple.remove(), 600);
        });
    });
    
    // Add ripple animation style
    const style = document.createElement('style');
    style.textContent = `
        @keyframes ripple {
            to { transform: scale(4); opacity: 0; }
        }
    `;
    document.head.appendChild(style);
});

// Log keyboard shortcuts info
console.log(`
SEMBox Dashboard Keyboard Shortcuts:
  1 - Toggle GPIO 26
  2 - Toggle GPIO 27
  3 - Toggle Built-in LED
  Shift+A - All ON
  Shift+O - All OFF
  R - Refresh Status
`);
