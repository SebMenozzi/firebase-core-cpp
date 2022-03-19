#include "firebase/auth.h"
#include "firebase/app.h"

class PhoneListener : public firebase::auth::PhoneAuthProvider::Listener {
    public:
        ~PhoneListener() override {}

        void OnVerificationCompleted(firebase::auth::Credential credential) override {
            // Auto-sms-retrieval or instant validation has succeeded (Android only).
            // No need for the user to input the verification code manually.
            // `credential` can be used instead of calling GetCredential().
        }

        void OnVerificationFailed(const std::string& error) override {
            // Verification code not sent.
        }

        void OnCodeSent(const std::string& verification_id, const firebase::auth::PhoneAuthProvider::ForceResendingToken& force_resending_token) override {
        // Verification code successfully sent via SMS.
        // Show the Screen to enter the Code.
        // Developer may want to save that verification_id along with other app states in case
        // the app is terminated before the user gets the SMS verification code.
        }
};
