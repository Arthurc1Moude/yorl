const vscode = require('vscode');
const path = require('path');
const fs = require('fs');
const os = require('os');

function activate(context) {
    console.log('Yorl extension is now active!');

    // Get the yolex binary path from extension
    const extensionPath = context.extensionPath;
    const yolexPath = path.join(extensionPath, 'yolex');

    // Make sure yolex is executable
    if (fs.existsSync(yolexPath)) {
        fs.chmodSync(yolexPath, '755');
        
        // Add to PATH for terminal
        const shellPath = process.env.PATH || '';
        if (!shellPath.includes(extensionPath)) {
            process.env.PATH = `${extensionPath}:${shellPath}`;
        }

        // Create symlink in user's local bin (optional, for system-wide access)
        const homeDir = os.homedir();
        const localBin = path.join(homeDir, '.local', 'bin');
        const symlinkPath = path.join(localBin, 'yolex');

        // Create .local/bin if it doesn't exist
        if (!fs.existsSync(localBin)) {
            fs.mkdirSync(localBin, { recursive: true });
        }

        // Create symlink if it doesn't exist
        if (!fs.existsSync(symlinkPath)) {
            try {
                fs.symlinkSync(yolexPath, symlinkPath);
                vscode.window.showInformationMessage('Yorl: yolex command is now available! Run "yolex --help" in terminal.');
            } catch (err) {
                console.log('Could not create symlink:', err.message);
            }
        }
    }

    // Register command to run yolex on current file
    let disposable = vscode.commands.registerCommand('yorl.compile', function () {
        const editor = vscode.window.activeTextEditor;
        if (editor) {
            const document = editor.document;
            if (document.languageId === 'yorl') {
                const terminal = vscode.window.createTerminal('Yorl');
                terminal.show();
                terminal.sendText(`yolex "${document.fileName}"`);
            } else {
                vscode.window.showWarningMessage('Current file is not a Yorl file');
            }
        }
    });

    context.subscriptions.push(disposable);
}

function deactivate() {}

module.exports = {
    activate,
    deactivate
};
